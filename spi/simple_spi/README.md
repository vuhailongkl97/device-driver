# STEP 
## 1. Config hardware  with dt overlay  
Uboot overlay , not use bone_capemgr due to this is no longer supported  
refer this to get more detail about [uboot overlay](https://elinux.org/Beagleboard:BeagleBoneBlack_Debian#U-Boot_Overlays)

## 2. Push data over SPI port

# NOTE  
when I try to use device tree overlay on BBB. I met some problem with my spi driver
BBB can load spi due to some SPI pin's configuration is conflict

conflict this  
```
spi@48030000 {

      channel@0{
 
      /* this look like okay when I try to probe SPI device from my SPI module*/
       compatible = "hea, long";
       status = "okay";
      }
  }
```
 
but when I try with channel-0 to change config of some SPI's PIN it look like okay.

[BeagleBone Black Device-Tree Overlay Generator](https://kilobaser.com/beaglebone-black-device-tree-overlay-generator/)
