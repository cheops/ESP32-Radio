// HX8357.h
//
// Contributed by Uksa007@gmail.com
// Separated from the main sketch to allow several display types.
// Includes for various HX8357 displays.  Tested on 320 x 240.
// Requires Adafruit HX8357 library, available from library manager.
// Below set your dsp_getwidth() and dsp_getwidth() to suite your display.

#include <Adafruit_HX8357.h>

// Color definitions for the TFT screen (if used)
// TFT has bits 6 bits (0..5) for RED, 6 bits (6..11) for GREEN and 4 bits (12..15) for BLUE.
#define BLACK   HX8357_BLACK
#define BLUE    HX8357_BLUE
#define RED     HX8357_RED
#define GREEN   HX8357_GREEN
#define CYAN    HX8357_CYAN
#define MAGENTA HX8357_MAGENTA
#define YELLOW  HX8357_YELLOW
#define WHITE   HX8357_WHITE

// Data to display.  There are TFTSECS sections
#define TFTSECS 4
// scrseg_struct     tftdata[TFTSECS] =                        // Screen divided in 3 segments + 1 overlay
// {                                                           // One text line is 8 pixels
//   { false, WHITE,   0,  8, "" },                            // 1 top line
//   { false, CYAN,   20, 64, "" },                            // 8 lines in the middle
//   { false, YELLOW, 90, 32, "" },                            // 4 lines at the bottom
//   { false, GREEN,  90, 32, "" }                             // 4 lines at the bottom for rotary encoder
// } ;
scrseg_struct     tftdata[TFTSECS] =                        // Screen divided in 3 segments + 1 overlay
{                                                           // One text line is 8 pixels
  { false, WHITE,  0,                 1*8*FONT_SIZE, "" },  // 1 top line
  { false, CYAN,   (1*8*FONT_SIZE)+4, 3*8*FONT_SIZE, "" },  // 3 lines in the middle
  { false, YELLOW, (5*8*FONT_SIZE)+4, 3*8*FONT_SIZE, "" },  // 3 lines at the bottom
  { false, GREEN,  (5*8*FONT_SIZE)+4, 3*8*FONT_SIZE, "" }   // 3 lines at the bottom for rotary encoder
} ;

Adafruit_HX8357*     tft = NULL ;                                  // For instance of display driver

// Various macro's to mimic the HX8357 version of display functions
#define dsp_setRotation()       tft->setRotation ( 3 )             // Use landscape format (3 for upside down)
#define dsp_print(a)            tft->print ( a )                   // Print a string 
#define dsp_println(b)          tft->println ( b )                 // Print a string followed by newline 
#define dsp_fillRect(a,b,c,d,e) tft->fillRect ( a, b, c, d, e ) ;  // Fill a rectange
#define dsp_setTextSize(a)      tft->setTextSize(a)                // Set the text size
#define dsp_setTextColor(a)     tft->setTextColor(a)               // Set the text color
#define dsp_setCursor(a,b)      tft->setCursor ( a, b )            // Position the cursor
#define dsp_erase()             tft->fillScreen ( BLACK ) ;        // Clear the screen
#define dsp_getwidth()          HX8357_TFTHEIGHT                   // Adjust to your display
#define dsp_getheight()         HX8357_TFTWIDTH                    // Get height of screen
#define dsp_update()                                               // Updates to the physical screen
#define dsp_usesSPI()           true                               // Does use SPI


bool dsp_begin()
{
  tft = new Adafruit_HX8357 ( ini_block.tft_cs_pin,
                               ini_block.tft_dc_pin ) ;            // Create an instant for TFT

  tft->begin();                                                    // Init TFT interface
  return ( tft != NULL ) ;
}

//**************************************************************************************************
//                                      D I S P L A Y B A T T E R Y                                *
//**************************************************************************************************
// Show the current battery charge level on the screen.                                            *
// It will overwrite the top divider.                                                              *
// No action if bat0/bat100 not defined in the preferences.                                        *
//**************************************************************************************************
void displaybattery()
{
  if ( tft )
  {
    if ( ini_block.bat0 < ini_block.bat100 )              // Levels set in preferences?
    {
      static uint16_t oldpos = 0 ;                        // Previous charge level
      uint16_t        ypos ;                              // Position on screen
      uint16_t        v ;                                 // Constrainted ADC value
      uint16_t        newpos ;                            // Current setting

      v = constrain ( adcval, ini_block.bat0,             // Prevent out of scale
                      ini_block.bat100 ) ;
      newpos = map ( v, ini_block.bat0,                   // Compute length of green bar
                     ini_block.bat100,
                     0, dsp_getwidth() ) ;
      if ( newpos != oldpos )                             // Value changed?
      {
        oldpos = newpos ;                                 // Remember for next compare
        ypos = tftdata[1].y - 5 ;                         // Just before 1st divider
        dsp_fillRect ( 0, ypos, newpos, 2, GREEN ) ;      // Paint green part
        dsp_fillRect ( newpos, ypos,
                       dsp_getwidth() - newpos,
                       2, RED ) ;                          // Paint red part
      }
    }
  }
}


//**************************************************************************************************
//                                      D I S P L A Y V O L U M E                                  *
//**************************************************************************************************
// Show the current volume as an indicator on the screen.                                          *
// The indicator is 2 pixels heigh.                                                                *
//**************************************************************************************************
void displayvolume()
{
  if ( tft )
  {
    static uint8_t oldvol = 0 ;                         // Previous volume
    uint8_t        newvol ;                             // Current setting
    uint16_t       len ;                                // Length of volume indicator in pixels

    char           voltxt[10] ;                         // 9 char + /0 termination
                                                        // longest string is "Vol 100 %"

    newvol = vs1053player->getVolume() ;                // Get current volume setting
    if ( newvol != oldvol )                             // Volume changed?
    {
      oldvol = newvol ;                                 // Remember for next compare
      len = map ( newvol, 0, 100, 0, dsp_getwidth() ) ; // Compute length on TFT
      dsp_fillRect ( 0, dsp_getheight() - ((8*FONT_SIZE)+1),
                     len, (8*FONT_SIZE)+1, RED ) ;                    // Paint red part
      dsp_fillRect ( len, dsp_getheight() - ((8*FONT_SIZE)+1),
                     dsp_getwidth() - len, (8*FONT_SIZE)+1, GREEN ) ; // Paint green part
      
      // one character is 6 wide and 8 high
      sprintf ( voltxt, "Vol % 3u %%", newvol ) ;       // format Volume to a string
      if (newvol<50) {
        dsp_setCursor(dsp_getwidth()-(6*FONT_SIZE*9), dsp_getheight()-(8*FONT_SIZE));
        dsp_setTextColor(BLACK);
        dsp_print(voltxt);
      } else {
        dsp_setCursor(0, dsp_getheight()-8*FONT_SIZE);
        dsp_setTextColor(WHITE);
        dsp_print(voltxt);
      }
    }
  }
}


//**************************************************************************************************
//                                      D I S P L A Y T I M E                                      *
//**************************************************************************************************
// Show the time on the LCD at a fixed position in a specified color                               *
// To prevent flickering, only the changed part of the timestring is displayed.                    *
// An empty string will force a refresh on next call.                                              *
// A character on the screen is 8 pixels high and 6 pixels wide.                                   *
//**************************************************************************************************
void displaytime ( const char* str, uint16_t color )
{
  static char oldstr[9] = "........" ;             // For compare
  uint8_t     i ;                                  // Index in strings
  uint16_t    pos = dsp_getwidth() + TIMEPOS ;     // X-position of character, TIMEPOS is negative

  if ( str[0] == '\0' )                            // Empty string?
  {
    for ( i = 0 ; i < 8 ; i++ )                    // Set oldstr to dots
    {
      oldstr[i] = '.' ;
    }
    return ;                                       // No actual display yet
  }
  if ( tft )                                       // TFT active?
  {
    dsp_setTextColor ( color ) ;                   // Set the requested color
    for ( i = 0 ; i < 8 ; i++ )                    // Compare old and new
    {
      if ( str[i] != oldstr[i] )                   // Difference?
      {
        dsp_fillRect ( pos, 0, 6*FONT_SIZE, 8*FONT_SIZE, BLACK ) ;     // Clear the space for new character
        dsp_setCursor ( pos, 0 ) ;                 // Prepare to show the info
        dsp_print ( str[i] ) ;                     // Show the character
        oldstr[i] = str[i] ;                       // Remember for next compare
      }
      pos += 6*FONT_SIZE ;                                   // Next position
    }
  }
}


