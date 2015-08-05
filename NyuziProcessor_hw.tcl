# TCL File Generated by Component Editor 13.0sp1
# Wed Jul 29 16:03:17 CST 2015
# DO NOT MODIFY


# 
# NyuziProcessor "NyuziProcessor" v1.0
# uestc 2015.07.29.16:03:17
# NyuziProcessor
# 

# 
# request TCL package from ACDS 13.1
# 
package require -exact qsys 13.1


# 
# module NyuziProcessor
# 
set_module_property DESCRIPTION NyuziProcessor
set_module_property NAME NyuziProcessor
set_module_property VERSION 1.0
set_module_property INTERNAL false
set_module_property OPAQUE_ADDRESS_MAP true
set_module_property GROUP "Embedded Processors"
set_module_property AUTHOR uestc
set_module_property DISPLAY_NAME NyuziProcessor
set_module_property INSTANTIATE_IN_SYSTEM_MODULE true
set_module_property EDITABLE true
set_module_property ANALYZE_HDL AUTO
set_module_property REPORT_TO_TALKBACK false
set_module_property ALLOW_GREYBOX_GENERATION false


# 
# file sets
# 
add_fileset QUARTUS_SYNTH QUARTUS_SYNTH "" ""
set_fileset_property QUARTUS_SYNTH TOP_LEVEL nyuzi
set_fileset_property QUARTUS_SYNTH ENABLE_RELATIVE_INCLUDE_PATHS false
add_fileset_file arbiter.sv SYSTEM_VERILOG PATH rtl/core/arbiter.sv
add_fileset_file cache_lru.sv SYSTEM_VERILOG PATH rtl/core/cache_lru.sv
add_fileset_file cam.sv SYSTEM_VERILOG PATH rtl/core/cam.sv
add_fileset_file config.sv SYSTEM_VERILOG PATH rtl/core/config.sv
add_fileset_file control_registers.sv SYSTEM_VERILOG PATH rtl/core/control_registers.sv
add_fileset_file core.sv SYSTEM_VERILOG PATH rtl/core/core.sv
add_fileset_file dcache_data_stage.sv SYSTEM_VERILOG PATH rtl/core/dcache_data_stage.sv
add_fileset_file dcache_tag_stage.sv SYSTEM_VERILOG PATH rtl/core/dcache_tag_stage.sv
add_fileset_file defines.sv SYSTEM_VERILOG PATH rtl/core/defines.sv
add_fileset_file fp_execute_stage1.sv SYSTEM_VERILOG PATH rtl/core/fp_execute_stage1.sv
add_fileset_file fp_execute_stage2.sv SYSTEM_VERILOG PATH rtl/core/fp_execute_stage2.sv
add_fileset_file fp_execute_stage3.sv SYSTEM_VERILOG PATH rtl/core/fp_execute_stage3.sv
add_fileset_file fp_execute_stage4.sv SYSTEM_VERILOG PATH rtl/core/fp_execute_stage4.sv
add_fileset_file fp_execute_stage5.sv SYSTEM_VERILOG PATH rtl/core/fp_execute_stage5.sv
add_fileset_file idx_to_oh.sv SYSTEM_VERILOG PATH rtl/core/idx_to_oh.sv
add_fileset_file ifetch_data_stage.sv SYSTEM_VERILOG PATH rtl/core/ifetch_data_stage.sv
add_fileset_file ifetch_tag_stage.sv SYSTEM_VERILOG PATH rtl/core/ifetch_tag_stage.sv
add_fileset_file instruction_decode_stage.sv SYSTEM_VERILOG PATH rtl/core/instruction_decode_stage.sv
add_fileset_file int_execute_stage.sv SYSTEM_VERILOG PATH rtl/core/int_execute_stage.sv
add_fileset_file io_arbiter.sv SYSTEM_VERILOG PATH rtl/core/io_arbiter.sv
add_fileset_file io_request_queue.sv SYSTEM_VERILOG PATH rtl/core/io_request_queue.sv
add_fileset_file l1_load_miss_queue.sv SYSTEM_VERILOG PATH rtl/core/l1_load_miss_queue.sv
add_fileset_file l1_store_queue.sv SYSTEM_VERILOG PATH rtl/core/l1_store_queue.sv
add_fileset_file l2_axi_bus_interface.sv SYSTEM_VERILOG PATH rtl/core/l2_axi_bus_interface.sv
add_fileset_file l2_cache.sv SYSTEM_VERILOG PATH rtl/core/l2_cache.sv
add_fileset_file l2_cache_arb.sv SYSTEM_VERILOG PATH rtl/core/l2_cache_arb.sv
add_fileset_file l2_cache_interface.sv SYSTEM_VERILOG PATH rtl/core/l2_cache_interface.sv
add_fileset_file l2_cache_pending_miss_cam.sv SYSTEM_VERILOG PATH rtl/core/l2_cache_pending_miss_cam.sv
add_fileset_file l2_cache_read.sv SYSTEM_VERILOG PATH rtl/core/l2_cache_read.sv
add_fileset_file l2_cache_tag.sv SYSTEM_VERILOG PATH rtl/core/l2_cache_tag.sv
add_fileset_file l2_cache_update.sv SYSTEM_VERILOG PATH rtl/core/l2_cache_update.sv
add_fileset_file nyuzi.sv SYSTEM_VERILOG PATH rtl/core/nyuzi.sv TOP_LEVEL_FILE
add_fileset_file oh_to_idx.sv SYSTEM_VERILOG PATH rtl/core/oh_to_idx.sv
add_fileset_file operand_fetch_stage.sv SYSTEM_VERILOG PATH rtl/core/operand_fetch_stage.sv
add_fileset_file performance_counters.sv SYSTEM_VERILOG PATH rtl/core/performance_counters.sv
add_fileset_file reciprocal_rom.sv SYSTEM_VERILOG PATH rtl/core/reciprocal_rom.sv
add_fileset_file sram_1r1w.sv SYSTEM_VERILOG PATH rtl/core/sram_1r1w.sv
add_fileset_file sram_2r1w.sv SYSTEM_VERILOG PATH rtl/core/sram_2r1w.sv
add_fileset_file sync_fifo.sv SYSTEM_VERILOG PATH rtl/core/sync_fifo.sv
add_fileset_file thread_select_stage.sv SYSTEM_VERILOG PATH rtl/core/thread_select_stage.sv
add_fileset_file writeback_stage.sv SYSTEM_VERILOG PATH rtl/core/writeback_stage.sv


# 
# parameters
# 
add_parameter RESET_PC INTEGER 0
set_parameter_property RESET_PC DEFAULT_VALUE 0
set_parameter_property RESET_PC DISPLAY_NAME RESET_PC
set_parameter_property RESET_PC TYPE INTEGER
set_parameter_property RESET_PC UNITS None
set_parameter_property RESET_PC ALLOWED_RANGES -2147483648:2147483647
set_parameter_property RESET_PC HDL_PARAMETER true


# 
# display items
# 


# 
# connection point clock
# 
add_interface clock clock end
set_interface_property clock clockRate 0
set_interface_property clock ENABLED true
set_interface_property clock EXPORT_OF ""
set_interface_property clock PORT_NAME_MAP ""
set_interface_property clock SVD_ADDRESS_GROUP ""

add_interface_port clock clk clk Input 1


# 
# connection point reset
# 
add_interface reset reset end
set_interface_property reset associatedClock clock
set_interface_property reset synchronousEdges DEASSERT
set_interface_property reset ENABLED true
set_interface_property reset EXPORT_OF ""
set_interface_property reset PORT_NAME_MAP ""
set_interface_property reset SVD_ADDRESS_GROUP ""

add_interface_port reset reset reset Input 1


# 
# connection point avalon_slave_0
# 
add_interface avalon_slave_0 avalon end
set_interface_property avalon_slave_0 addressUnits WORDS
set_interface_property avalon_slave_0 associatedClock clock
set_interface_property avalon_slave_0 associatedReset ""
set_interface_property avalon_slave_0 bitsPerSymbol 8
set_interface_property avalon_slave_0 burstOnBurstBoundariesOnly false
set_interface_property avalon_slave_0 burstcountUnits WORDS
set_interface_property avalon_slave_0 explicitAddressSpan 0
set_interface_property avalon_slave_0 holdTime 0
set_interface_property avalon_slave_0 linewrapBursts false
set_interface_property avalon_slave_0 maximumPendingReadTransactions 0
set_interface_property avalon_slave_0 readLatency 0
set_interface_property avalon_slave_0 readWaitTime 1
set_interface_property avalon_slave_0 setupTime 0
set_interface_property avalon_slave_0 timingUnits Cycles
set_interface_property avalon_slave_0 writeWaitTime 0
set_interface_property avalon_slave_0 ENABLED true
set_interface_property avalon_slave_0 EXPORT_OF ""
set_interface_property avalon_slave_0 PORT_NAME_MAP ""
set_interface_property avalon_slave_0 SVD_ADDRESS_GROUP ""

add_interface_port avalon_slave_0 processor_halt writeresponsevalid_n Output 1
add_interface_port avalon_slave_0 interrupt_req writeresponserequest_n Input 1
add_interface_port avalon_slave_0 axi_bus writeresponsevalid_n Output 1
set_interface_assignment avalon_slave_0 embeddedsw.configuration.isFlash 0
set_interface_assignment avalon_slave_0 embeddedsw.configuration.isMemoryDevice 0
set_interface_assignment avalon_slave_0 embeddedsw.configuration.isNonVolatileStorage 0
set_interface_assignment avalon_slave_0 embeddedsw.configuration.isPrintableDevice 0


# 
# connection point altera_axi4_master
# 
add_interface altera_axi4_master axi4 start
set_interface_property altera_axi4_master associatedClock clock
set_interface_property altera_axi4_master associatedReset ""
set_interface_property altera_axi4_master readIssuingCapability 1
set_interface_property altera_axi4_master writeIssuingCapability 1
set_interface_property altera_axi4_master combinedIssuingCapability 1
set_interface_property altera_axi4_master ENABLED true
set_interface_property altera_axi4_master EXPORT_OF ""
set_interface_property altera_axi4_master PORT_NAME_MAP ""
set_interface_property altera_axi4_master SVD_ADDRESS_GROUP ""

add_interface_port altera_axi4_master io_write_en awvalid Output 1
add_interface_port altera_axi4_master io_read_en arvalid Output 1
add_interface_port altera_axi4_master io_address araddr Output 32
add_interface_port altera_axi4_master io_write_data wdata Output 32
add_interface_port altera_axi4_master io_read_data rdata Input 32


# 
# connection point ahb_master
# 
add_interface ahb_master ahb start
set_interface_property ahb_master associatedClock clock
set_interface_property ahb_master associatedReset ""
set_interface_property ahb_master ENABLED true
set_interface_property ahb_master EXPORT_OF ""
set_interface_property ahb_master PORT_NAME_MAP ""
set_interface_property ahb_master SVD_ADDRESS_GROUP ""

