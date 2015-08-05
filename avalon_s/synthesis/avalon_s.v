// avalon_s.v

// Generated using ACDS version 13.0sp1 232 at 2015.07.29.15:22:11

`timescale 1 ps / 1 ps
module avalon_s (
		input  wire  clk_clk,       //   clk.clk
		input  wire  reset_reset_n  // reset.reset_n
	);

	wire    rst_controller_reset_out_reset; // rst_controller:reset_out -> merlin_master_agent_0:reset

	altera_merlin_master_agent #(
		.PKT_PROTECTION_H          (80),
		.PKT_PROTECTION_L          (80),
		.PKT_BEGIN_BURST           (81),
		.PKT_BURSTWRAP_H           (79),
		.PKT_BURSTWRAP_L           (77),
		.PKT_BURST_SIZE_H          (86),
		.PKT_BURST_SIZE_L          (84),
		.PKT_BURST_TYPE_H          (94),
		.PKT_BURST_TYPE_L          (93),
		.PKT_BYTE_CNT_H            (76),
		.PKT_BYTE_CNT_L            (74),
		.PKT_ADDR_H                (73),
		.PKT_ADDR_L                (42),
		.PKT_TRANS_COMPRESSED_READ (41),
		.PKT_TRANS_POSTED          (40),
		.PKT_TRANS_WRITE           (39),
		.PKT_TRANS_READ            (38),
		.PKT_TRANS_LOCK            (82),
		.PKT_TRANS_EXCLUSIVE       (83),
		.PKT_DATA_H                (37),
		.PKT_DATA_L                (6),
		.PKT_BYTEEN_H              (5),
		.PKT_BYTEEN_L              (2),
		.PKT_SRC_ID_H              (1),
		.PKT_SRC_ID_L              (1),
		.PKT_DEST_ID_H             (0),
		.PKT_DEST_ID_L             (0),
		.PKT_THREAD_ID_H           (88),
		.PKT_THREAD_ID_L           (87),
		.PKT_CACHE_H               (92),
		.PKT_CACHE_L               (89),
		.PKT_DATA_SIDEBAND_H       (105),
		.PKT_DATA_SIDEBAND_L       (98),
		.PKT_QOS_H                 (109),
		.PKT_QOS_L                 (106),
		.PKT_ADDR_SIDEBAND_H       (97),
		.PKT_ADDR_SIDEBAND_L       (93),
		.PKT_RESPONSE_STATUS_H     (111),
		.PKT_RESPONSE_STATUS_L     (110),
		.ST_DATA_W                 (112),
		.ST_CHANNEL_W              (1),
		.AV_BURSTCOUNT_W           (3),
		.SUPPRESS_0_BYTEEN_RSP     (1),
		.ID                        (1),
		.BURSTWRAP_VALUE           (4),
		.CACHE_VALUE               (0),
		.SECURE_ACCESS_BIT         (1),
		.USE_READRESPONSE          (0),
		.USE_WRITERESPONSE         (0)
	) merlin_master_agent_0 (
		.clk                     (clk_clk),                        //       clk.clk
		.reset                   (rst_controller_reset_out_reset), // clk_reset.reset
		.av_address              (),                               //        av.address
		.av_write                (),                               //          .write
		.av_read                 (),                               //          .read
		.av_writedata            (),                               //          .writedata
		.av_readdata             (),                               //          .readdata
		.av_waitrequest          (),                               //          .waitrequest
		.av_readdatavalid        (),                               //          .readdatavalid
		.av_byteenable           (),                               //          .byteenable
		.av_burstcount           (),                               //          .burstcount
		.av_debugaccess          (),                               //          .debugaccess
		.av_lock                 (),                               //          .lock
		.cp_valid                (),                               //        cp.valid
		.cp_data                 (),                               //          .data
		.cp_startofpacket        (),                               //          .startofpacket
		.cp_endofpacket          (),                               //          .endofpacket
		.cp_ready                (),                               //          .ready
		.rp_valid                (),                               //        rp.valid
		.rp_data                 (),                               //          .data
		.rp_channel              (),                               //          .channel
		.rp_startofpacket        (),                               //          .startofpacket
		.rp_endofpacket          (),                               //          .endofpacket
		.rp_ready                (),                               //          .ready
		.av_response             (),                               // (terminated)
		.av_writeresponserequest (1'b0),                           // (terminated)
		.av_writeresponsevalid   ()                                // (terminated)
	);

	altera_reset_controller #(
		.NUM_RESET_INPUTS        (1),
		.OUTPUT_RESET_SYNC_EDGES ("deassert"),
		.SYNC_DEPTH              (2),
		.RESET_REQUEST_PRESENT   (0)
	) rst_controller (
		.reset_in0  (~reset_reset_n),                 // reset_in0.reset
		.clk        (clk_clk),                        //       clk.clk
		.reset_out  (rst_controller_reset_out_reset), // reset_out.reset
		.reset_req  (),                               // (terminated)
		.reset_in1  (1'b0),                           // (terminated)
		.reset_in2  (1'b0),                           // (terminated)
		.reset_in3  (1'b0),                           // (terminated)
		.reset_in4  (1'b0),                           // (terminated)
		.reset_in5  (1'b0),                           // (terminated)
		.reset_in6  (1'b0),                           // (terminated)
		.reset_in7  (1'b0),                           // (terminated)
		.reset_in8  (1'b0),                           // (terminated)
		.reset_in9  (1'b0),                           // (terminated)
		.reset_in10 (1'b0),                           // (terminated)
		.reset_in11 (1'b0),                           // (terminated)
		.reset_in12 (1'b0),                           // (terminated)
		.reset_in13 (1'b0),                           // (terminated)
		.reset_in14 (1'b0),                           // (terminated)
		.reset_in15 (1'b0)                            // (terminated)
	);

endmodule