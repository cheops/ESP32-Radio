// Default preferences in raw data format for PROGMEM
//
#define defaultprefs_version 23052022
const char defprefs_txt[] PROGMEM = R"=====(
# Example configuration
# Programmable input pins:
#gpio_00 = uppreset = 1
#gpio_12 = upvolume = 2
#gpio_13 = downvolume = 2
#gpio_14 = stop
#gpio_17 = resume
#gpio_34 = station = icecast.omroep.nl:80/radio1-bb-mp3
#
# MQTT settings
#mqttbroker = none
#mqttport = 1883
#mqttuser = none
#mqttpasswd = none
#mqqprefix = none
# Enter your WiFi network specs here:
wifi_00 = SSID1/PASSWD1
#wifi_01 = SSID2/PASSWD2
#
volume = 72
toneha = 0
tonehf = 0
tonela = 0
tonelf = 0
#
preset = 3
# Some preset examples
preset_00 = icecast.vrtcdn.be/radio1-high.mp3                                # Radio 1
preset_01 = icecast.vrtcdn.be/klaracontinuo-high.mp3                         # Klara Continuo
preset_02 = icecast.vrtcdn.be/stubru-high.mp3                                # Studio Brussel
preset_03 = icecast.vrtcdn.be/mnm-high.mp3                                   # MNM
preset_04 = icecast.vrtcdn.be/mnm_urb-high.mp3                               # MNM R&Beats
preset_05 = icecast.vrtcdn.be/mnm_hits-high.mp3                              # MNM Hits
preset_06 = icecast.vrtcdn.be/mnm_90s00s-high.mp3                            # MNM Throwback
preset_07 = progressive-audio.vrtcdn.be/content/fixed/11_11niws-snip_hi.mp3  # VRT NWS
preset_08 = icecast.vrtcdn.be/radio1_classics-high.mp3                       # Radio 1 classics
preset_09 = icecast.vrtcdn.be/radio1_lagelanden-high.mp3                     # Radio 1 DeLageLandenLijst
preset_10 = icecast.vrtcdn.be/radio2_benebene-high.mp3                       # Radio 2 Bene Bene
preset_11 = icecast.vrtcdn.be/ra2ant-high.mp3                                # Radio 2 Antwerpen
preset_12 = icecast.vrtcdn.be/radio2_unwind-high.mp3                         # Radio 2 Unwind
preset_13 = icecast.vrtcdn.be/klara-high.mp3                                 # Klara
preset_14 = icecast.vrtcdn.be/stubru_bruut-high.mp3                          # Studio Brussel - Bruut
preset_15 = icecast.vrtcdn.be/stubru_hiphophooray-high.mp3                   # Studio Brussel - Hooray
preset_16 = icecast.vrtcdn.be/stubru_tijdloze-high.mp3                       # Studio Brussel - De Tijdloze
preset_17 = icecast.vrtcdn.be/stubru_tgs-high.mp3                            # Studio Brussel - Vuurland
preset_18 = icecast.vrtcdn.be/stubru_untz-high.mp3                           # Studio Brussel - UNTZ
preset_19 = icecast.vrtcdn.be/ketnetradio-high.mp3                           # Ketnet Hits
#
# Clock offset and daylight saving time
clk_server = pool.ntp.org                            # Time server to be used
clk_offset = 1                                       # Offset with respect to UTC in hours
clk_dst = 1                                          # Offset during daylight saving time (hours)
# Some IR codes
#ir_40BF = upvolume = 2
#ir_C03F = downvolume = 2
# GPIO pinnings
#pin_ir = 35                                          # GPIO Pin number for IR receiver VS1838B
#pin_enc_clk = 25                                     # GPIO Pin number for rotary encoder "CLK"
#pin_enc_dt = 26                                      # GPIO Pin number for rotary encoder "DT"
#pin_enc_sw = 27                                      # GPIO Pin number for rotary encoder "SW"
#
pin_tft_cs = 15                                      # GPIO Pin number for TFT "CS"
pin_tft_dc = 33                                       # GPIO Pin number for TFT "DC"
#
#pin_sd_cs = 21                                       # GPIO Pin number for SD card "CS"
#
pin_vs_cs = 17                                        # GPIO Pin number for VS1053 "CS"
pin_vs_dcs = 16                                      # GPIO Pin number for VS1053 "DCS"
pin_vs_dreq = 4                                      # GPIO Pin number for VS1053 "DREQ"
)=====" ;
