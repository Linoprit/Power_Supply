/ext/JLink_Linux_V680c_x86_64/JLinkExe -device STM32F303RE -if SWD -speed 400 -autoconnect 1 -CommandFile commandFile.jlink
#/usr/bin/st-flash --reset --format ihex write ./Debug/PowerSupply_F303.hex
