// number of overlays (w/o fusion): 6 
// number of overlays (w/ fusion): 6 
#include <sys/time.h> 
#include <algorithm> 
#include <cstring> 
#include <fstream> 
#include <iomanip> 
#include <iostream> 
#include <sstream> 
#include <climits> 
#include <unordered_map> 
const int PU_NM = 8; 

#include "table_dt.hpp" 
#include "utils.hpp" 
#include "tpch_read_2.hpp" 
#include "gqe_api.hpp" 

#include "cfgFunc_q8.hpp" 
#include "q8.hpp" 

int main(int argc, const char* argv[]) { 
    std::cout << "\n------------ TPC-H Query Test -------------\n"; 
    ArgParser parser(argc, argv); 
    std::string xclbin_path; 
    if (!parser.getCmdOption("-xclbin", xclbin_path)) { 
        std::cout << "ERROR: xclbin path is not set!\n"; 
        return 1; 
    } 
    std::string xclbin_path_h; 
    if (!parser.getCmdOption("-xclbin_h", xclbin_path_h)) { 
        std::cout << "ERROR: xclbin_h path is not set!\n"; 
        return 1; 
    } 
    std::string xclbin_path_a; 
    if (!parser.getCmdOption("-xclbin_a", xclbin_path_a)) { 
        std::cout << "ERROR: xclbin_a path is not set!\n"; 
        return 1; 
    } 
    std::string in_dir; 
    if (!parser.getCmdOption("-in", in_dir) || !is_dir(in_dir)) { 
        std::cout << "ERROR: input dir is not specified or not valid.\n"; 
        return 1; 
    } 
    int num_rep = 1; 
    std::string num_str; 
    if (parser.getCmdOption("-rep", num_str)) { 
        try { 
            num_rep = std::stoi(num_str); 
        } catch (...) { 
            num_rep = 1; 
        } 
    } 
    if (num_rep > 20) { 
        num_rep = 20; 
        std::cout << "WARNING: limited repeat to " << num_rep << " times\n."; 
    } 
    int scale = 1; 
    std::string scale_str; 
    if (parser.getCmdOption("-c", scale_str)) { 
        try { 
            scale = std::stoi(scale_str); 
        } catch (...) { 
            scale = 1; 
        } 
    } 
    std::cout << "NOTE:running query #8\n."; 
    std::cout << "NOTE:running in sf" << scale << " data\n"; 

    int32_t lineitem_n = SF1_LINEITEM; 
    int32_t supplier_n = SF1_SUPPLIER; 
    int32_t nation_n = SF1_NATION; 
    int32_t orders_n = SF1_ORDERS; 
    int32_t customer_n = SF1_CUSTOMER; 
    int32_t region_n = SF1_REGION; 
    int32_t part_n = SF1_PART; 
    int32_t partsupp_n = SF1_PARTSUPP; 
    if (scale == 30) { 
        lineitem_n = SF30_LINEITEM; 
        supplier_n = SF30_SUPPLIER; 
        nation_n = SF30_NATION; 
        orders_n = SF30_ORDERS; 
        customer_n = SF30_CUSTOMER; 
        region_n = SF30_REGION; 
        part_n = SF30_PART; 
        partsupp_n = SF30_PARTSUPP; 
    } 
    // ********************************************************** // 
    // Get CL devices. 
    std::vector<cl::Device> devices = xcl::get_xil_devices(); 
    cl::Device device_h = devices[0]; 
    // Create context_h and command queue for selected device 
    cl::Context context_h(device_h); 
    cl::CommandQueue q_h(context_h, device_h, CL_QUEUE_PROFILING_ENABLE | CL_QUEUE_OUT_OF_ORDER_EXEC_MODE_ENABLE); 
    std::string devName_h = device_h.getInfo<CL_DEVICE_NAME>(); 
    std::cout << "Selected Device " << devName_h << "\n"; 
    cl::Program::Binaries xclBins_h = xcl::import_binary_file(xclbin_path_h); 
    std::vector<cl::Device> devices_h; 
    devices_h.push_back(device_h); 
    cl::Program program_h(context_h, devices_h, xclBins_h); 
    // ****************************** Tables **************************** // 
    Table tbl_Sort_TD_0545_output("tbl_Sort_TD_0545_output", 6100000, 2, "");
    tbl_Sort_TD_0545_output.allocateHost();
    Table tbl_Aggregate_TD_1736_output("tbl_Aggregate_TD_1736_output", 6100000, 2, "");
    tbl_Aggregate_TD_1736_output.allocateHost();
    Table tbl_Project_TD_2676_output("tbl_Project_TD_2676_output", 6100000, 3, "");
    tbl_Project_TD_2676_output.allocateHost();
    Table tbl_JOIN_INNER_TD_3840_output("tbl_JOIN_INNER_TD_3840_output", 6100000, 4, "");
    tbl_JOIN_INNER_TD_3840_output.allocateHost();
    Table tbl_JOIN_INNER_TD_4702_output("tbl_JOIN_INNER_TD_4702_output", 2539, 5, "");
    tbl_JOIN_INNER_TD_4702_output.allocateHost();
    Table tbl_SerializeFromObject_TD_4509_input;
    tbl_SerializeFromObject_TD_4509_input = Table("nation", nation_n, 2, in_dir);
    tbl_SerializeFromObject_TD_4509_input.addCol("n_nationkey", 4);
    tbl_SerializeFromObject_TD_4509_input.addCol("n_name", TPCH_READ_NATION_LEN+1);
    tbl_SerializeFromObject_TD_4509_input.allocateHost();
    tbl_SerializeFromObject_TD_4509_input.loadHost();
    Table tbl_JOIN_INNER_TD_5622_output("tbl_JOIN_INNER_TD_5622_output", 12215, 5, "");
    tbl_JOIN_INNER_TD_5622_output.allocateHost();
    Table tbl_Filter_TD_4473_output("tbl_Filter_TD_4473_output", 6100000, 1, "");
    tbl_Filter_TD_4473_output.allocateHost();
    Table tbl_JOIN_INNER_TD_6198_output("tbl_JOIN_INNER_TD_6198_output", 12215, 5, "");
    tbl_JOIN_INNER_TD_6198_output.allocateHost();
    Table tbl_SerializeFromObject_TD_614_input;
    tbl_SerializeFromObject_TD_614_input = Table("nation", nation_n, 2, in_dir);
    tbl_SerializeFromObject_TD_614_input.addCol("n_nationkey", 4);
    tbl_SerializeFromObject_TD_614_input.addCol("n_regionkey", 4);
    tbl_SerializeFromObject_TD_614_input.allocateHost();
    tbl_SerializeFromObject_TD_614_input.loadHost();
    Table tbl_SerializeFromObject_TD_5515_input;
    tbl_SerializeFromObject_TD_5515_input = Table("region", region_n, 2, in_dir);
    tbl_SerializeFromObject_TD_5515_input.addCol("r_regionkey", 4);
    tbl_SerializeFromObject_TD_5515_input.addCol("r_name", TPCH_READ_REGION_LEN+1);
    tbl_SerializeFromObject_TD_5515_input.allocateHost();
    tbl_SerializeFromObject_TD_5515_input.loadHost();
    Table tbl_JOIN_INNER_TD_7830_output("tbl_JOIN_INNER_TD_7830_output", 12215, 5, "");
    tbl_JOIN_INNER_TD_7830_output.allocateHost();
    Table tbl_SerializeFromObject_TD_7814_input;
    tbl_SerializeFromObject_TD_7814_input = Table("customer", customer_n, 2, in_dir);
    tbl_SerializeFromObject_TD_7814_input.addCol("c_custkey", 4);
    tbl_SerializeFromObject_TD_7814_input.addCol("c_nationkey", 4);
    tbl_SerializeFromObject_TD_7814_input.allocateHost();
    tbl_SerializeFromObject_TD_7814_input.loadHost();
    Table tbl_JOIN_INNER_TD_8790_output("tbl_JOIN_INNER_TD_8790_output", 39720, 4, "");
    tbl_JOIN_INNER_TD_8790_output.allocateHost();
    Table tbl_Filter_TD_8847_output("tbl_Filter_TD_8847_output", 6100000, 3, "");
    tbl_Filter_TD_8847_output.allocateHost();
    Table tbl_JOIN_INNER_TD_9824_output("tbl_JOIN_INNER_TD_9824_output", 39720, 4, "");
    tbl_JOIN_INNER_TD_9824_output.allocateHost();
    Table tbl_SerializeFromObject_TD_9120_input;
    tbl_SerializeFromObject_TD_9120_input = Table("supplier", supplier_n, 2, in_dir);
    tbl_SerializeFromObject_TD_9120_input.addCol("s_suppkey", 4);
    tbl_SerializeFromObject_TD_9120_input.addCol("s_nationkey", 4);
    tbl_SerializeFromObject_TD_9120_input.allocateHost();
    tbl_SerializeFromObject_TD_9120_input.loadHost();
    Table tbl_SerializeFromObject_TD_9848_input;
    tbl_SerializeFromObject_TD_9848_input = Table("orders", orders_n, 3, in_dir);
    tbl_SerializeFromObject_TD_9848_input.addCol("o_orderkey", 4);
    tbl_SerializeFromObject_TD_9848_input.addCol("o_custkey", 4);
    tbl_SerializeFromObject_TD_9848_input.addCol("o_orderdate", 4);
    tbl_SerializeFromObject_TD_9848_input.allocateHost();
    tbl_SerializeFromObject_TD_9848_input.loadHost();
    Table tbl_Filter_TD_10125_output("tbl_Filter_TD_10125_output", 6100000, 1, "");
    tbl_Filter_TD_10125_output.allocateHost();
    Table tbl_SerializeFromObject_TD_10330_input;
    tbl_SerializeFromObject_TD_10330_input = Table("lineitem", lineitem_n, 5, in_dir);
    tbl_SerializeFromObject_TD_10330_input.addCol("l_orderkey", 4);
    tbl_SerializeFromObject_TD_10330_input.addCol("l_partkey", 4);
    tbl_SerializeFromObject_TD_10330_input.addCol("l_suppkey", 4);
    tbl_SerializeFromObject_TD_10330_input.addCol("l_extendedprice", 4);
    tbl_SerializeFromObject_TD_10330_input.addCol("l_discount", 4);
    tbl_SerializeFromObject_TD_10330_input.allocateHost();
    tbl_SerializeFromObject_TD_10330_input.loadHost();
    Table tbl_SerializeFromObject_TD_11681_input;
    tbl_SerializeFromObject_TD_11681_input = Table("part", part_n, 2, in_dir);
    tbl_SerializeFromObject_TD_11681_input.addCol("p_partkey", 4);
    tbl_SerializeFromObject_TD_11681_input.addCol("p_type", TPCH_READ_P_TYPE_LEN+1);
    tbl_SerializeFromObject_TD_11681_input.allocateHost();
    tbl_SerializeFromObject_TD_11681_input.loadHost();
    // ********************** Allocate Device Buffer ******************** // 
    tbl_JOIN_INNER_TD_4702_output.allocateDevBuffer(context_h, 32);
    tbl_JOIN_INNER_TD_5622_output.allocateDevBuffer(context_h, 32);
    tbl_Filter_TD_4473_output.allocateDevBuffer(context_h, 32);
    tbl_JOIN_INNER_TD_6198_output.allocateDevBuffer(context_h, 32);
    tbl_SerializeFromObject_TD_614_input.allocateDevBuffer(context_h, 32);
    tbl_JOIN_INNER_TD_7830_output.allocateDevBuffer(context_h, 32);
    tbl_SerializeFromObject_TD_7814_input.allocateDevBuffer(context_h, 32);
    tbl_JOIN_INNER_TD_8790_output.allocateDevBuffer(context_h, 32);
    tbl_Filter_TD_8847_output.allocateDevBuffer(context_h, 32);
    tbl_JOIN_INNER_TD_9824_output.allocateDevBuffer(context_h, 32);
    tbl_SerializeFromObject_TD_9120_input.allocateDevBuffer(context_h, 32);
    tbl_Filter_TD_10125_output.allocateDevBuffer(context_h, 32);
    tbl_SerializeFromObject_TD_10330_input.allocateDevBuffer(context_h, 32);
    // ****************************** Config **************************** // 
    cfgCmd cfg_JOIN_INNER_TD_4702_cmds;
    cfg_JOIN_INNER_TD_4702_cmds.allocateHost();
    get_cfg_dat_JOIN_INNER_TD_4702_gqe_join (cfg_JOIN_INNER_TD_4702_cmds.cmd);
    cfg_JOIN_INNER_TD_4702_cmds.allocateDevBuffer(context_h, 32);
    cfgCmd cfg_JOIN_INNER_TD_5622_cmds;
    cfg_JOIN_INNER_TD_5622_cmds.allocateHost();
    get_cfg_dat_JOIN_INNER_TD_5622_gqe_join (cfg_JOIN_INNER_TD_5622_cmds.cmd);
    cfg_JOIN_INNER_TD_5622_cmds.allocateDevBuffer(context_h, 32);
    cfgCmd cfg_JOIN_INNER_TD_6198_cmds;
    cfg_JOIN_INNER_TD_6198_cmds.allocateHost();
    get_cfg_dat_JOIN_INNER_TD_6198_gqe_join (cfg_JOIN_INNER_TD_6198_cmds.cmd);
    cfg_JOIN_INNER_TD_6198_cmds.allocateDevBuffer(context_h, 32);
    cfgCmd cfg_JOIN_INNER_TD_7830_cmds;
    cfg_JOIN_INNER_TD_7830_cmds.allocateHost();
    get_cfg_dat_JOIN_INNER_TD_7830_gqe_join (cfg_JOIN_INNER_TD_7830_cmds.cmd);
    cfg_JOIN_INNER_TD_7830_cmds.allocateDevBuffer(context_h, 32);
    cfgCmd cfg_JOIN_INNER_TD_8790_cmds;
    cfg_JOIN_INNER_TD_8790_cmds.allocateHost();
    get_cfg_dat_JOIN_INNER_TD_8790_gqe_join (cfg_JOIN_INNER_TD_8790_cmds.cmd);
    cfg_JOIN_INNER_TD_8790_cmds.allocateDevBuffer(context_h, 32);
    cfgCmd cfg_JOIN_INNER_TD_9824_cmds;
    cfg_JOIN_INNER_TD_9824_cmds.allocateHost();
    get_cfg_dat_JOIN_INNER_TD_9824_gqe_join (cfg_JOIN_INNER_TD_9824_cmds.cmd);
    cfg_JOIN_INNER_TD_9824_cmds.allocateDevBuffer(context_h, 32);
    // *************************** Kernel Setup ************************* // 
    bufferTmp buftmp_h(context_h); 
    buftmp_h.initBuffer(q_h); 
    std::cout << std::endl; 
    krnlEngine krnl_JOIN_INNER_TD_4702;
    krnl_JOIN_INNER_TD_4702 = krnlEngine(program_h, q_h, "gqeJoin");
    krnl_JOIN_INNER_TD_4702.setup(tbl_Filter_TD_4473_output, tbl_JOIN_INNER_TD_5622_output, tbl_JOIN_INNER_TD_4702_output, cfg_JOIN_INNER_TD_4702_cmds, buftmp_h);
    krnlEngine krnl_JOIN_INNER_TD_5622;
    krnl_JOIN_INNER_TD_5622 = krnlEngine(program_h, q_h, "gqeJoin");
    krnl_JOIN_INNER_TD_5622.setup(tbl_SerializeFromObject_TD_614_input, tbl_JOIN_INNER_TD_6198_output, tbl_JOIN_INNER_TD_5622_output, cfg_JOIN_INNER_TD_5622_cmds, buftmp_h);
    krnlEngine krnl_JOIN_INNER_TD_6198;
    krnl_JOIN_INNER_TD_6198 = krnlEngine(program_h, q_h, "gqeJoin");
    krnl_JOIN_INNER_TD_6198.setup(tbl_JOIN_INNER_TD_7830_output, tbl_SerializeFromObject_TD_7814_input, tbl_JOIN_INNER_TD_6198_output, cfg_JOIN_INNER_TD_6198_cmds, buftmp_h);
    krnlEngine krnl_JOIN_INNER_TD_7830;
    krnl_JOIN_INNER_TD_7830 = krnlEngine(program_h, q_h, "gqeJoin");
    krnl_JOIN_INNER_TD_7830.setup(tbl_JOIN_INNER_TD_8790_output, tbl_Filter_TD_8847_output, tbl_JOIN_INNER_TD_7830_output, cfg_JOIN_INNER_TD_7830_cmds, buftmp_h);
    krnlEngine krnl_JOIN_INNER_TD_8790;
    krnl_JOIN_INNER_TD_8790 = krnlEngine(program_h, q_h, "gqeJoin");
    krnl_JOIN_INNER_TD_8790.setup(tbl_SerializeFromObject_TD_9120_input, tbl_JOIN_INNER_TD_9824_output, tbl_JOIN_INNER_TD_8790_output, cfg_JOIN_INNER_TD_8790_cmds, buftmp_h);
    krnlEngine krnl_JOIN_INNER_TD_9824;
    krnl_JOIN_INNER_TD_9824 = krnlEngine(program_h, q_h, "gqeJoin");
    krnl_JOIN_INNER_TD_9824.setup(tbl_Filter_TD_10125_output, tbl_SerializeFromObject_TD_10330_input, tbl_JOIN_INNER_TD_9824_output, cfg_JOIN_INNER_TD_9824_cmds, buftmp_h);
    // ************************** Transfer Engine *********************** // 
    transEngine trans_JOIN_INNER_TD_4702;
    trans_JOIN_INNER_TD_4702.setq(q_h);
    trans_JOIN_INNER_TD_4702.add(&(cfg_JOIN_INNER_TD_4702_cmds));
    transEngine trans_JOIN_INNER_TD_4702_out;
    trans_JOIN_INNER_TD_4702_out.setq(q_h);
    q_h.finish();
    transEngine trans_JOIN_INNER_TD_5622;
    trans_JOIN_INNER_TD_5622.setq(q_h);
    trans_JOIN_INNER_TD_5622.add(&(cfg_JOIN_INNER_TD_5622_cmds));
    trans_JOIN_INNER_TD_5622.add(&(tbl_SerializeFromObject_TD_614_input));
    q_h.finish();
    transEngine trans_JOIN_INNER_TD_6198;
    trans_JOIN_INNER_TD_6198.setq(q_h);
    trans_JOIN_INNER_TD_6198.add(&(cfg_JOIN_INNER_TD_6198_cmds));
    trans_JOIN_INNER_TD_6198.add(&(tbl_SerializeFromObject_TD_7814_input));
    q_h.finish();
    transEngine trans_JOIN_INNER_TD_7830;
    trans_JOIN_INNER_TD_7830.setq(q_h);
    trans_JOIN_INNER_TD_7830.add(&(cfg_JOIN_INNER_TD_7830_cmds));
    q_h.finish();
    transEngine trans_JOIN_INNER_TD_8790;
    trans_JOIN_INNER_TD_8790.setq(q_h);
    trans_JOIN_INNER_TD_8790.add(&(cfg_JOIN_INNER_TD_8790_cmds));
    trans_JOIN_INNER_TD_8790.add(&(tbl_SerializeFromObject_TD_9120_input));
    q_h.finish();
    transEngine trans_JOIN_INNER_TD_9824;
    trans_JOIN_INNER_TD_9824.setq(q_h);
    trans_JOIN_INNER_TD_9824.add(&(cfg_JOIN_INNER_TD_9824_cmds));
    trans_JOIN_INNER_TD_9824.add(&(tbl_SerializeFromObject_TD_10330_input));
    q_h.finish();
    // ****************************** Events **************************** // 
    std::vector<cl::Event> events_h2d_wr_JOIN_INNER_TD_4702;
    std::vector<cl::Event> events_d2h_rd_JOIN_INNER_TD_4702;
    std::vector<cl::Event> events_JOIN_INNER_TD_4702;
    events_h2d_wr_JOIN_INNER_TD_4702.resize(1);
    events_d2h_rd_JOIN_INNER_TD_4702.resize(1);
    events_JOIN_INNER_TD_4702.resize(1);
    std::vector<cl::Event> events_grp_JOIN_INNER_TD_4702;
    std::vector<cl::Event> prev_events_grp_JOIN_INNER_TD_4702;
    std::vector<cl::Event> events_h2d_wr_JOIN_INNER_TD_5622;
    std::vector<cl::Event> events_d2h_rd_JOIN_INNER_TD_5622;
    std::vector<cl::Event> events_JOIN_INNER_TD_5622;
    events_h2d_wr_JOIN_INNER_TD_5622.resize(1);
    events_d2h_rd_JOIN_INNER_TD_5622.resize(1);
    events_JOIN_INNER_TD_5622.resize(1);
    std::vector<cl::Event> events_grp_JOIN_INNER_TD_5622;
    std::vector<cl::Event> prev_events_grp_JOIN_INNER_TD_5622;
    std::vector<cl::Event> events_h2d_wr_JOIN_INNER_TD_6198;
    std::vector<cl::Event> events_d2h_rd_JOIN_INNER_TD_6198;
    std::vector<cl::Event> events_JOIN_INNER_TD_6198;
    events_h2d_wr_JOIN_INNER_TD_6198.resize(1);
    events_d2h_rd_JOIN_INNER_TD_6198.resize(1);
    events_JOIN_INNER_TD_6198.resize(1);
    std::vector<cl::Event> events_grp_JOIN_INNER_TD_6198;
    std::vector<cl::Event> prev_events_grp_JOIN_INNER_TD_6198;
    std::vector<cl::Event> events_h2d_wr_JOIN_INNER_TD_7830;
    std::vector<cl::Event> events_d2h_rd_JOIN_INNER_TD_7830;
    std::vector<cl::Event> events_JOIN_INNER_TD_7830;
    events_h2d_wr_JOIN_INNER_TD_7830.resize(1);
    events_d2h_rd_JOIN_INNER_TD_7830.resize(1);
    events_JOIN_INNER_TD_7830.resize(1);
    std::vector<cl::Event> events_grp_JOIN_INNER_TD_7830;
    std::vector<cl::Event> prev_events_grp_JOIN_INNER_TD_7830;
    std::vector<cl::Event> events_h2d_wr_JOIN_INNER_TD_8790;
    std::vector<cl::Event> events_d2h_rd_JOIN_INNER_TD_8790;
    std::vector<cl::Event> events_JOIN_INNER_TD_8790;
    events_h2d_wr_JOIN_INNER_TD_8790.resize(1);
    events_d2h_rd_JOIN_INNER_TD_8790.resize(1);
    events_JOIN_INNER_TD_8790.resize(1);
    std::vector<cl::Event> events_grp_JOIN_INNER_TD_8790;
    std::vector<cl::Event> prev_events_grp_JOIN_INNER_TD_8790;
    std::vector<cl::Event> events_h2d_wr_JOIN_INNER_TD_9824;
    std::vector<cl::Event> events_d2h_rd_JOIN_INNER_TD_9824;
    std::vector<cl::Event> events_JOIN_INNER_TD_9824;
    events_h2d_wr_JOIN_INNER_TD_9824.resize(1);
    events_d2h_rd_JOIN_INNER_TD_9824.resize(1);
    events_JOIN_INNER_TD_9824.resize(1);
    std::vector<cl::Event> events_grp_JOIN_INNER_TD_9824;
    std::vector<cl::Event> prev_events_grp_JOIN_INNER_TD_9824;
    // **************************** Operations ************************** // 
    struct timeval tv_r_s, tv_r_e; 
    gettimeofday(&tv_r_s, 0); 

    struct timeval tv_r_Filter_10_356_s, tv_r_Filter_10_356_e;
    gettimeofday(&tv_r_Filter_10_356_s, 0);
    SW_Filter_TD_10125(tbl_SerializeFromObject_TD_11681_input, tbl_Filter_TD_10125_output);
    gettimeofday(&tv_r_Filter_10_356_e, 0);

    struct timeval tv_r_JOIN_INNER_9_752_s, tv_r_JOIN_INNER_9_752_e;
    gettimeofday(&tv_r_JOIN_INNER_9_752_s, 0);
    trans_JOIN_INNER_TD_9824.add(&(tbl_Filter_TD_10125_output));
    trans_JOIN_INNER_TD_9824.host2dev(0, &(prev_events_grp_JOIN_INNER_TD_9824), &(events_h2d_wr_JOIN_INNER_TD_9824[0]));
    events_grp_JOIN_INNER_TD_9824.push_back(events_h2d_wr_JOIN_INNER_TD_9824[0]);
    krnl_JOIN_INNER_TD_9824.run(0, &(events_grp_JOIN_INNER_TD_9824), &(events_JOIN_INNER_TD_9824[0]));
    gettimeofday(&tv_r_JOIN_INNER_9_752_e, 0);

    struct timeval tv_r_Filter_8_531_s, tv_r_Filter_8_531_e;
    gettimeofday(&tv_r_Filter_8_531_s, 0);
    SW_Filter_TD_8847(tbl_SerializeFromObject_TD_9848_input, tbl_Filter_TD_8847_output);
    gettimeofday(&tv_r_Filter_8_531_e, 0);

    struct timeval tv_r_JOIN_INNER_8_145_s, tv_r_JOIN_INNER_8_145_e;
    gettimeofday(&tv_r_JOIN_INNER_8_145_s, 0);
    prev_events_grp_JOIN_INNER_TD_8790.push_back(events_h2d_wr_JOIN_INNER_TD_9824[0]);
    trans_JOIN_INNER_TD_8790.host2dev(0, &(prev_events_grp_JOIN_INNER_TD_8790), &(events_h2d_wr_JOIN_INNER_TD_8790[0]));
    events_grp_JOIN_INNER_TD_8790.push_back(events_h2d_wr_JOIN_INNER_TD_8790[0]);
    events_grp_JOIN_INNER_TD_8790.push_back(events_JOIN_INNER_TD_9824[0]);
    krnl_JOIN_INNER_TD_8790.run(0, &(events_grp_JOIN_INNER_TD_8790), &(events_JOIN_INNER_TD_8790[0]));
    gettimeofday(&tv_r_JOIN_INNER_8_145_e, 0);

    struct timeval tv_r_JOIN_INNER_7_355_s, tv_r_JOIN_INNER_7_355_e;
    gettimeofday(&tv_r_JOIN_INNER_7_355_s, 0);
    prev_events_grp_JOIN_INNER_TD_7830.push_back(events_h2d_wr_JOIN_INNER_TD_8790[0]);
    trans_JOIN_INNER_TD_7830.add(&(tbl_Filter_TD_8847_output));
    trans_JOIN_INNER_TD_7830.host2dev(0, &(prev_events_grp_JOIN_INNER_TD_7830), &(events_h2d_wr_JOIN_INNER_TD_7830[0]));
    events_grp_JOIN_INNER_TD_7830.push_back(events_h2d_wr_JOIN_INNER_TD_7830[0]);
    events_grp_JOIN_INNER_TD_7830.push_back(events_JOIN_INNER_TD_8790[0]);
    krnl_JOIN_INNER_TD_7830.run(0, &(events_grp_JOIN_INNER_TD_7830), &(events_JOIN_INNER_TD_7830[0]));
    gettimeofday(&tv_r_JOIN_INNER_7_355_e, 0);

    struct timeval tv_r_JOIN_INNER_6_499_s, tv_r_JOIN_INNER_6_499_e;
    gettimeofday(&tv_r_JOIN_INNER_6_499_s, 0);
    prev_events_grp_JOIN_INNER_TD_6198.push_back(events_h2d_wr_JOIN_INNER_TD_7830[0]);
    trans_JOIN_INNER_TD_6198.host2dev(0, &(prev_events_grp_JOIN_INNER_TD_6198), &(events_h2d_wr_JOIN_INNER_TD_6198[0]));
    events_grp_JOIN_INNER_TD_6198.push_back(events_h2d_wr_JOIN_INNER_TD_6198[0]);
    events_grp_JOIN_INNER_TD_6198.push_back(events_JOIN_INNER_TD_7830[0]);
    krnl_JOIN_INNER_TD_6198.run(0, &(events_grp_JOIN_INNER_TD_6198), &(events_JOIN_INNER_TD_6198[0]));
    gettimeofday(&tv_r_JOIN_INNER_6_499_e, 0);

    struct timeval tv_r_Filter_4_981_s, tv_r_Filter_4_981_e;
    gettimeofday(&tv_r_Filter_4_981_s, 0);
    SW_Filter_TD_4473(tbl_SerializeFromObject_TD_5515_input, tbl_Filter_TD_4473_output);
    gettimeofday(&tv_r_Filter_4_981_e, 0);

    struct timeval tv_r_JOIN_INNER_5_843_s, tv_r_JOIN_INNER_5_843_e;
    gettimeofday(&tv_r_JOIN_INNER_5_843_s, 0);
    prev_events_grp_JOIN_INNER_TD_5622.push_back(events_h2d_wr_JOIN_INNER_TD_6198[0]);
    trans_JOIN_INNER_TD_5622.host2dev(0, &(prev_events_grp_JOIN_INNER_TD_5622), &(events_h2d_wr_JOIN_INNER_TD_5622[0]));
    events_grp_JOIN_INNER_TD_5622.push_back(events_h2d_wr_JOIN_INNER_TD_5622[0]);
    events_grp_JOIN_INNER_TD_5622.push_back(events_JOIN_INNER_TD_6198[0]);
    krnl_JOIN_INNER_TD_5622.run(0, &(events_grp_JOIN_INNER_TD_5622), &(events_JOIN_INNER_TD_5622[0]));
    gettimeofday(&tv_r_JOIN_INNER_5_843_e, 0);

    struct timeval tv_r_JOIN_INNER_4_78_s, tv_r_JOIN_INNER_4_78_e;
    gettimeofday(&tv_r_JOIN_INNER_4_78_s, 0);
    prev_events_grp_JOIN_INNER_TD_4702.push_back(events_h2d_wr_JOIN_INNER_TD_5622[0]);
    trans_JOIN_INNER_TD_4702.add(&(tbl_Filter_TD_4473_output));
    trans_JOIN_INNER_TD_4702.host2dev(0, &(prev_events_grp_JOIN_INNER_TD_4702), &(events_h2d_wr_JOIN_INNER_TD_4702[0]));
    events_grp_JOIN_INNER_TD_4702.push_back(events_h2d_wr_JOIN_INNER_TD_4702[0]);
    events_grp_JOIN_INNER_TD_4702.push_back(events_JOIN_INNER_TD_5622[0]);
    krnl_JOIN_INNER_TD_4702.run(0, &(events_grp_JOIN_INNER_TD_4702), &(events_JOIN_INNER_TD_4702[0]));
    
    trans_JOIN_INNER_TD_4702_out.add(&(tbl_JOIN_INNER_TD_4702_output));
    trans_JOIN_INNER_TD_4702_out.dev2host(0, &(events_JOIN_INNER_TD_4702), &(events_d2h_rd_JOIN_INNER_TD_4702[0]));
    q_h.flush();
    q_h.finish();
    gettimeofday(&tv_r_JOIN_INNER_4_78_e, 0);

    struct timeval tv_r_JOIN_INNER_3_779_s, tv_r_JOIN_INNER_3_779_e;
    gettimeofday(&tv_r_JOIN_INNER_3_779_s, 0);
    SW_JOIN_INNER_TD_3840(tbl_JOIN_INNER_TD_4702_output, tbl_SerializeFromObject_TD_4509_input, tbl_JOIN_INNER_TD_3840_output);
    gettimeofday(&tv_r_JOIN_INNER_3_779_e, 0);

    struct timeval tv_r_Project_2_42_s, tv_r_Project_2_42_e;
    gettimeofday(&tv_r_Project_2_42_s, 0);
    SW_Project_TD_2676(tbl_JOIN_INNER_TD_3840_output, tbl_Project_TD_2676_output);
    gettimeofday(&tv_r_Project_2_42_e, 0);

    struct timeval tv_r_Aggregate_1_294_s, tv_r_Aggregate_1_294_e;
    gettimeofday(&tv_r_Aggregate_1_294_s, 0);
    SW_Aggregate_TD_1736(tbl_Project_TD_2676_output, tbl_Aggregate_TD_1736_output);
    gettimeofday(&tv_r_Aggregate_1_294_e, 0);

    struct timeval tv_r_Sort_0_374_s, tv_r_Sort_0_374_e;
    gettimeofday(&tv_r_Sort_0_374_s, 0);
    SW_Sort_TD_0545(tbl_Aggregate_TD_1736_output, tbl_Sort_TD_0545_output);
    gettimeofday(&tv_r_Sort_0_374_e, 0);

    gettimeofday(&tv_r_e, 0); 
    // **************************** Print Execution Time ************************** // 
    std::cout << "Filter_10: " << tvdiff(&tv_r_Filter_10_356_s, &tv_r_Filter_10_356_e) / 1000.0 << " ms " 
     << "tbl_SerializeFromObject_TD_11681_input: " << tbl_SerializeFromObject_TD_11681_input.getNumRow() << " " << std::endl; 

    std::cout << "JOIN_INNER_9: " << tvdiff(&tv_r_JOIN_INNER_9_752_s, &tv_r_JOIN_INNER_9_752_e) / 1000.0 << " ms " 
     << "tbl_Filter_TD_10125_output: " << tbl_Filter_TD_10125_output.getNumRow() << " " << "tbl_SerializeFromObject_TD_10330_input: " << tbl_SerializeFromObject_TD_10330_input.getNumRow() << " " << std::endl; 

    std::cout << "Filter_8: " << tvdiff(&tv_r_Filter_8_531_s, &tv_r_Filter_8_531_e) / 1000.0 << " ms " 
     << "tbl_SerializeFromObject_TD_9848_input: " << tbl_SerializeFromObject_TD_9848_input.getNumRow() << " " << std::endl; 

    std::cout << "JOIN_INNER_8: " << tvdiff(&tv_r_JOIN_INNER_8_145_s, &tv_r_JOIN_INNER_8_145_e) / 1000.0 << " ms " 
     << "tbl_JOIN_INNER_TD_9824_output: " << tbl_JOIN_INNER_TD_9824_output.getNumRow() << " " << "tbl_SerializeFromObject_TD_9120_input: " << tbl_SerializeFromObject_TD_9120_input.getNumRow() << " " << std::endl; 

    std::cout << "JOIN_INNER_7: " << tvdiff(&tv_r_JOIN_INNER_7_355_s, &tv_r_JOIN_INNER_7_355_e) / 1000.0 << " ms " 
     << "tbl_JOIN_INNER_TD_8790_output: " << tbl_JOIN_INNER_TD_8790_output.getNumRow() << " " << "tbl_Filter_TD_8847_output: " << tbl_Filter_TD_8847_output.getNumRow() << " " << std::endl; 

    std::cout << "JOIN_INNER_6: " << tvdiff(&tv_r_JOIN_INNER_6_499_s, &tv_r_JOIN_INNER_6_499_e) / 1000.0 << " ms " 
     << "tbl_JOIN_INNER_TD_7830_output: " << tbl_JOIN_INNER_TD_7830_output.getNumRow() << " " << "tbl_SerializeFromObject_TD_7814_input: " << tbl_SerializeFromObject_TD_7814_input.getNumRow() << " " << std::endl; 

    std::cout << "Filter_4: " << tvdiff(&tv_r_Filter_4_981_s, &tv_r_Filter_4_981_e) / 1000.0 << " ms " 
     << "tbl_SerializeFromObject_TD_5515_input: " << tbl_SerializeFromObject_TD_5515_input.getNumRow() << " " << std::endl; 

    std::cout << "JOIN_INNER_5: " << tvdiff(&tv_r_JOIN_INNER_5_843_s, &tv_r_JOIN_INNER_5_843_e) / 1000.0 << " ms " 
     << "tbl_JOIN_INNER_TD_6198_output: " << tbl_JOIN_INNER_TD_6198_output.getNumRow() << " " << "tbl_SerializeFromObject_TD_614_input: " << tbl_SerializeFromObject_TD_614_input.getNumRow() << " " << std::endl; 

    std::cout << "JOIN_INNER_4: " << tvdiff(&tv_r_JOIN_INNER_4_78_s, &tv_r_JOIN_INNER_4_78_e) / 1000.0 << " ms " 
     << "tbl_JOIN_INNER_TD_5622_output: " << tbl_JOIN_INNER_TD_5622_output.getNumRow() << " " << "tbl_Filter_TD_4473_output: " << tbl_Filter_TD_4473_output.getNumRow() << " " << std::endl; 

    std::cout << "JOIN_INNER_3: " << tvdiff(&tv_r_JOIN_INNER_3_779_s, &tv_r_JOIN_INNER_3_779_e) / 1000.0 << " ms " 
     << "tbl_JOIN_INNER_TD_4702_output: " << tbl_JOIN_INNER_TD_4702_output.getNumRow() << " " << "tbl_SerializeFromObject_TD_4509_input: " << tbl_SerializeFromObject_TD_4509_input.getNumRow() << " " << std::endl; 

    std::cout << "Project_2: " << tvdiff(&tv_r_Project_2_42_s, &tv_r_Project_2_42_e) / 1000.0 << " ms " 
     << "tbl_JOIN_INNER_TD_3840_output: " << tbl_JOIN_INNER_TD_3840_output.getNumRow() << " " << std::endl; 

    std::cout << "Aggregate_1: " << tvdiff(&tv_r_Aggregate_1_294_s, &tv_r_Aggregate_1_294_e) / 1000.0 << " ms " 
     << "tbl_Project_TD_2676_output: " << tbl_Project_TD_2676_output.getNumRow() << " " << std::endl; 

    std::cout << "Sort_0: " << tvdiff(&tv_r_Sort_0_374_s, &tv_r_Sort_0_374_e) / 1000.0 << " ms " 
     << "tbl_Aggregate_TD_1736_output: " << tbl_Aggregate_TD_1736_output.getNumRow() << " " << std::endl; 

    std::cout << std::endl << " Total execution time: " << tvdiff(&tv_r_s, &tv_r_e) / 1000 << " ms"; 

    std::cout << std::endl << " Spark elapsed time: " << 38.492004 * 1000 << "ms" << std::endl; 
    return 0; 
}
