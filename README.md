## OpenWrt Feeds

This Git contains an OpenWrt feed. The main purpose is an in system low-voltage programmer for PIC Microcontroller.

### OpenWrt Compiling

To use this feed just edit your feeds.conf or feeds.conf.default in the OpenWrt root dir:

```src-git pickleprog https://github.com/datachi7d/openwrt-pickle```

Update the feeds and install the pickleprog feed

```
scripts/feeds update
scripts/feeds install pickleprog
```

### Ci40 hardware setup

The connections for the programming interface on the Ci40 use the raspberry pi connector as shown below. The raspberry pi connector is the longest connector on the board, next to the mikro-bus connector. The image below shows the connector in relation to the mikro-bus connectors, the power barrel and reset button.

```
 ............._____..._--_...........................
             | PWR | |RST |                         .
             |     |                                .
             |     |                                .
                                                    .
              MFIO_85 40|39		  0 0 0 0 0 0 0 0   .
              MFIO_84 38|37                         .
              MFIO_82 36|35                         .
              GND     34|33                         .
                      32|31         1               .
                      30|29                         .
                      28|27                         .
                      26|25                         .
                      24|23		  0 0 0 0 0 0 0 0   .
                      22|21                         .
                      20|19                         .
                      17|15		  0 0 0 0 0 0 0 0   .
                      14|13                         .
                      12|11                         .
                      10|9                          .
                      8 |7          2               .
                      6 |5                          .
                      4 |3                          .
                      2 |1  3v3                     .
                                  0 0 0 0 0 0 0 0   .
                                                    .
```

Connect the pins above to the clicker as following

```
MFIO_85 ->  PGC
MFIO_84 ->  PGD
MFIO_82 ->  RST
GND     ->  GND
3v3     ->  3v3
```

### Using pickle programmer

Test connection with:

``` p32 info ```
