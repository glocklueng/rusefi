
rem Let's wipe out all local libraries. Frankenstein does not have it's own libraries!
rm lib/*.*

rem Let's copy Analog Input libraries & schematic 
cp ../adc_amp_divider/lib/* lib/
cp ../adc_amp_divider.vertical/adc_amp_divider_vert.sch .

rem Same thing for 6 channel board
cp ../1A_injector_6-channels/lib/* lib/
cp ../1A_injector_6-channels/inj_6ch.sch .

rem MMC/TTL module
cp ../usb_mmc_spi/lib/* lib/
cp ../usb_mmc_spi/mmc_usb_1.sch .

rem Now let's merge all compoennt mappings automatically. Magic!
java -jar ../../java_tools/pcb_sync.jar cmp_merge frankenstein.cmp ../1A_injector_6-channels/inj_6ch.cmp ../adc_amp_divider.vertival/adc_amp_divider_vert.cmp ../usb_mmc_spi/mmc_usb_1.cmp

rem Let's merge these PCBs into the Frankenstein!
java -jar ../../java_tools/pcb_sync.jar pcb_merge frankenstein_template.kicad_pcb frankenstein.kicad_pcb ../1A_injector_6-channels/inj_6ch.kicad_pcb ../adc_amp_divider.vertical/adc_amp_divider_vert.kicad_pcb ../usb_mmc_spi/mmc_usb_1.kicad_pcb