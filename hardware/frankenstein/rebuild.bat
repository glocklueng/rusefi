
rem Let's wipe out all local libraries. Frankenstein does not have it's own libraries!
mkdir lib
rm lib/*.*
mkdir lib/3d
rm lib/3d/*.*


rem Let's copy Analog Input libraries & schematic 
cp ../adc_amp_divider/lib/* lib/
cp ../adc_amp_divider.vertical12/adc_amp_divider.sch .

rem Same thing for 6 channel board
cp ../1A_injector_6-channels/lib/* lib/
cp ../1A_injector_6-channels/inj_6ch.sch .

rem MMC/TTL module
cp -r ../usb_mmc_spi/lib/* lib/
cp ../usb_mmc_spi/mmc_usb_1.sch .

rem VR input
cp -r ../knock_VR_Art_ELectro/lib/* lib/
cp -r ../knock_VR_Art_ELectro/cps_vrs_io_1.sch .

cp ../frankenstein_foundation/frankenstein_foundation.sch .

cp ../can_board/lib/* lib/
cp ../can_board/lib/3d/* lib/3d
cp ../can_board/can_brd_1.sch .

rem Now let's merge all compoennt mappings automatically. Magic!
java -jar ../../java_tools/pcb_sync.jar cmp_merge frankenstein.cmp ../can_board/can_brd_1.cmp ../1A_injector_6-channels/inj_6ch.cmp ../adc_amp_divider.vertical12/adc_amp_divider.cmp ../usb_mmc_spi/mmc_usb_1.cmp ../frankenstein_foundation/frankenstein_foundation.cmp ../knock_VR_Art_ELectro/cps_vrs_io_1.cmp

rem Let's merge these PCBs into the Frankenstein!
java -jar ../../java_tools/pcb_sync.jar pcb_merge ../frankenstein_foundation/frankenstein_foundation.kicad_pcb frankenstein.kicad_pcb ../can_board/can_brd_1.kicad_pcb ../1A_injector_6-channels/inj_6ch.kicad_pcb ../adc_amp_divider.vertical12/adc_amp_divider.kicad_pcb ../usb_mmc_spi/mmc_usb_1.kicad_pcb ../knock_VR_Art_ELectro/cps_vrs_io_1.kicad_pcb
