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

#include "cfgFunc_q20.hpp" 
#include "q20.hpp" 

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
    std::cout << "NOTE:running query #20\n."; 
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
    cl::Device device_a = devices[1]; 
    // Create context_a and command queue for selected device 
    cl::Context context_a(device_a); 
    cl::CommandQueue q_a(context_a, device_a, CL_QUEUE_PROFILING_ENABLE | CL_QUEUE_OUT_OF_ORDER_EXEC_MODE_ENABLE); 
    std::string devName_a = device_a.getInfo<CL_DEVICE_NAME>(); 
    std::cout << "Selected Device " << devName_a << "\n"; 
    cl::Program::Binaries xclBins_a = xcl::import_binary_file(xclbin_path_a); 
    std::vector<cl::Device> devices_a; 
    devices_a.push_back(device_a); 
    cl::Program program_a(context_a, devices_a, xclBins_a); 
    // ****************************** Tables **************************** // 
    Table tbl_Sort_TD_0293_output("tbl_Sort_TD_0293_output", 6100000, 2, "");
    tbl_Sort_TD_0293_output.allocateHost();
    Table tbl_JOIN_INNER_TD_1206_output("tbl_JOIN_INNER_TD_1206_output", 210, 2, "");
    tbl_JOIN_INNER_TD_1206_output.allocateHost();
    Table tbl_JOIN_LEFTSEMI_TD_2858_output("tbl_JOIN_LEFTSEMI_TD_2858_output", 5366, 3, "");
    tbl_JOIN_LEFTSEMI_TD_2858_output.allocateHost();
    Table tbl_Filter_TD_2767_output("tbl_Filter_TD_2767_output", 6100000, 1, "");
    tbl_Filter_TD_2767_output.allocateHost();
    Table tbl_SerializeFromObject_TD_3269_input_stringRowIDSubstitute;
    tbl_SerializeFromObject_TD_3269_input_stringRowIDSubstitute = Table("supplier", supplier_n, 4, in_dir);
    tbl_SerializeFromObject_TD_3269_input_stringRowIDSubstitute.addCol("s_suppkey", 4);
    tbl_SerializeFromObject_TD_3269_input_stringRowIDSubstitute.addCol("s_name", 4, 1, 0);
    tbl_SerializeFromObject_TD_3269_input_stringRowIDSubstitute.addCol("s_address", 4, 1, 0);
    tbl_SerializeFromObject_TD_3269_input_stringRowIDSubstitute.addCol("s_nationkey", 4);
    tbl_SerializeFromObject_TD_3269_input_stringRowIDSubstitute.allocateHost();
    tbl_SerializeFromObject_TD_3269_input_stringRowIDSubstitute.loadHost();
    Table tbl_SerializeFromObject_TD_3269_input;
    tbl_SerializeFromObject_TD_3269_input = Table("supplier", supplier_n, 4, in_dir);
    tbl_SerializeFromObject_TD_3269_input.addCol("s_suppkey", 4);
    tbl_SerializeFromObject_TD_3269_input.addCol("s_name", TPCH_READ_S_NAME_LEN+1);
    tbl_SerializeFromObject_TD_3269_input.addCol("s_address", TPCH_READ_S_ADDR_MAX+1);
    tbl_SerializeFromObject_TD_3269_input.addCol("s_nationkey", 4);
    tbl_SerializeFromObject_TD_3269_input.allocateHost();
    tbl_SerializeFromObject_TD_3269_input.loadHost();
    Table tbl_JOIN_INNER_TD_3119_output("tbl_JOIN_INNER_TD_3119_output", 7670, 1, "");
    tbl_JOIN_INNER_TD_3119_output.allocateHost();
    Table tbl_SerializeFromObject_TD_3798_input;
    tbl_SerializeFromObject_TD_3798_input = Table("nation", nation_n, 2, in_dir);
    tbl_SerializeFromObject_TD_3798_input.addCol("n_nationkey", 4);
    tbl_SerializeFromObject_TD_3798_input.addCol("n_name", TPCH_READ_NATION_LEN+1);
    tbl_SerializeFromObject_TD_3798_input.allocateHost();
    tbl_SerializeFromObject_TD_3798_input.loadHost();
    Table tbl_JOIN_LEFTSEMI_TD_4303_output("tbl_JOIN_LEFTSEMI_TD_4303_output", 11160, 3, "");
    tbl_JOIN_LEFTSEMI_TD_4303_output.allocateHost();
    Table tbl_Aggregate_TD_5342_output_preprocess("tbl_Aggregate_TD_5342_output_preprocess", 15000, 16, "");
    tbl_Aggregate_TD_5342_output_preprocess.allocateHost();
    Table tbl_Aggregate_TD_5342_output("tbl_Aggregate_TD_5342_output", 15000, 3, "");
    tbl_Aggregate_TD_5342_output.allocateHost();
    Table tbl_SerializeFromObject_TD_587_input;
    tbl_SerializeFromObject_TD_587_input = Table("partsupp", partsupp_n, 3, in_dir);
    tbl_SerializeFromObject_TD_587_input.addCol("ps_partkey", 4);
    tbl_SerializeFromObject_TD_587_input.addCol("ps_suppkey", 4);
    tbl_SerializeFromObject_TD_587_input.addCol("ps_availqty", 4);
    tbl_SerializeFromObject_TD_587_input.allocateHost();
    tbl_SerializeFromObject_TD_587_input.loadHost();
    Table tbl_JOIN_LEFTSEMI_TD_6448_output_preprocess("tbl_JOIN_LEFTSEMI_TD_6448_output_preprocess", 12816, 3, "");
    tbl_JOIN_LEFTSEMI_TD_6448_output_preprocess.allocateHost();
    Table tbl_JOIN_LEFTSEMI_TD_6448_output("tbl_JOIN_LEFTSEMI_TD_6448_output", 12816, 3, "");
    tbl_JOIN_LEFTSEMI_TD_6448_output.allocateHost();
    Table tbl_Filter_TD_760_output("tbl_Filter_TD_760_output", 6100000, 3, "");
    tbl_Filter_TD_760_output.allocateHost();
    Table tbl_Filter_TD_7153_output("tbl_Filter_TD_7153_output", 6100000, 1, "");
    tbl_Filter_TD_7153_output.allocateHost();
    Table tbl_SerializeFromObject_TD_8615_input;
    tbl_SerializeFromObject_TD_8615_input = Table("lineitem", lineitem_n, 4, in_dir);
    tbl_SerializeFromObject_TD_8615_input.addCol("l_partkey", 4);
    tbl_SerializeFromObject_TD_8615_input.addCol("l_suppkey", 4);
    tbl_SerializeFromObject_TD_8615_input.addCol("l_quantity", 4);
    tbl_SerializeFromObject_TD_8615_input.addCol("l_shipdate", 4);
    tbl_SerializeFromObject_TD_8615_input.allocateHost();
    tbl_SerializeFromObject_TD_8615_input.loadHost();
    Table tbl_SerializeFromObject_TD_8916_input;
    tbl_SerializeFromObject_TD_8916_input = Table("part", part_n, 2, in_dir);
    tbl_SerializeFromObject_TD_8916_input.addCol("p_partkey", 4);
    tbl_SerializeFromObject_TD_8916_input.addCol("p_name", TPCH_READ_P_NAME_LEN+1);
    tbl_SerializeFromObject_TD_8916_input.allocateHost();
    tbl_SerializeFromObject_TD_8916_input.loadHost();
    // ********************** Allocate Device Buffer ******************** // 
    tbl_JOIN_INNER_TD_1206_output.allocateDevBuffer(context_h, 32);
    tbl_JOIN_LEFTSEMI_TD_2858_output.allocateDevBuffer(context_h, 32);
    tbl_Filter_TD_2767_output.allocateDevBuffer(context_h, 32);
    tbl_SerializeFromObject_TD_3269_input_stringRowIDSubstitute.allocateDevBuffer(context_h, 32);
    tbl_JOIN_INNER_TD_3119_output.allocateDevBuffer(context_h, 32);
    tbl_JOIN_LEFTSEMI_TD_4303_output.allocateDevBuffer(context_h, 32);
    tbl_JOIN_LEFTSEMI_TD_6448_output.allocateDevBuffer(context_a, 32);
    tbl_Aggregate_TD_5342_output_preprocess.allocateDevBuffer(context_a, 33);
    tbl_Aggregate_TD_5342_output.allocateDevBuffer(context_h, 32);
    tbl_SerializeFromObject_TD_587_input.allocateDevBuffer(context_h, 32);
    tbl_JOIN_LEFTSEMI_TD_6448_output_preprocess.allocateDevBuffer(context_h, 32);
    tbl_Filter_TD_760_output.allocateDevBuffer(context_h, 32);
    tbl_Filter_TD_7153_output.allocateDevBuffer(context_h, 32);
    // ****************************** Config **************************** // 
    cfgCmd cfg_JOIN_INNER_TD_1206_cmds;
    cfg_JOIN_INNER_TD_1206_cmds.allocateHost();
    get_cfg_dat_JOIN_INNER_TD_1206_gqe_join (cfg_JOIN_INNER_TD_1206_cmds.cmd);
    cfg_JOIN_INNER_TD_1206_cmds.allocateDevBuffer(context_h, 32);
    cfgCmd cfg_JOIN_LEFTSEMI_TD_2858_cmds;
    cfg_JOIN_LEFTSEMI_TD_2858_cmds.allocateHost();
    get_cfg_dat_JOIN_LEFTSEMI_TD_2858_gqe_join (cfg_JOIN_LEFTSEMI_TD_2858_cmds.cmd);
    cfg_JOIN_LEFTSEMI_TD_2858_cmds.allocateDevBuffer(context_h, 32);
    cfgCmd cfg_JOIN_INNER_TD_3119_cmds;
    cfg_JOIN_INNER_TD_3119_cmds.allocateHost();
    get_cfg_dat_JOIN_INNER_TD_3119_gqe_join (cfg_JOIN_INNER_TD_3119_cmds.cmd);
    cfg_JOIN_INNER_TD_3119_cmds.allocateDevBuffer(context_h, 32);
    cfgCmd cfg_JOIN_LEFTSEMI_TD_4303_cmds;
    cfg_JOIN_LEFTSEMI_TD_4303_cmds.allocateHost();
    get_cfg_dat_JOIN_LEFTSEMI_TD_4303_gqe_join (cfg_JOIN_LEFTSEMI_TD_4303_cmds.cmd);
    cfg_JOIN_LEFTSEMI_TD_4303_cmds.allocateDevBuffer(context_h, 32);
    AggrCfgCmd cfg_Aggregate_TD_5342_cmds;
    cfg_Aggregate_TD_5342_cmds.allocateHost();
    get_cfg_dat_Aggregate_TD_5342_gqe_aggr(cfg_Aggregate_TD_5342_cmds.cmd);
    cfg_Aggregate_TD_5342_cmds.allocateDevBuffer(context_a, 32);
    AggrCfgCmd cfg_Aggregate_TD_5342_cmds_out;
    cfg_Aggregate_TD_5342_cmds_out.allocateHost();
    cfg_Aggregate_TD_5342_cmds_out.allocateDevBuffer(context_a, 33);
    cfgCmd cfg_JOIN_LEFTSEMI_TD_6448_cmds;
    cfg_JOIN_LEFTSEMI_TD_6448_cmds.allocateHost();
    get_cfg_dat_JOIN_LEFTSEMI_TD_6448_gqe_join (cfg_JOIN_LEFTSEMI_TD_6448_cmds.cmd);
    cfg_JOIN_LEFTSEMI_TD_6448_cmds.allocateDevBuffer(context_h, 32);
    // *************************** Kernel Setup ************************* // 
    bufferTmp buftmp_h(context_h); 
    buftmp_h.initBuffer(q_h); 
    AggrBufferTmp buftmp_a(context_a); 
    buftmp_a.BufferInitial(q_a); 
    std::cout << std::endl; 
    krnlEngine krnl_JOIN_INNER_TD_1206;
    krnl_JOIN_INNER_TD_1206 = krnlEngine(program_h, q_h, "gqeJoin");
    krnl_JOIN_INNER_TD_1206.setup(tbl_JOIN_LEFTSEMI_TD_2858_output, tbl_Filter_TD_2767_output, tbl_JOIN_INNER_TD_1206_output, cfg_JOIN_INNER_TD_1206_cmds, buftmp_h);
    krnlEngine krnl_JOIN_LEFTSEMI_TD_2858;
    krnl_JOIN_LEFTSEMI_TD_2858 = krnlEngine(program_h, q_h, "gqeJoin");
    krnl_JOIN_LEFTSEMI_TD_2858.setup(tbl_JOIN_INNER_TD_3119_output, tbl_SerializeFromObject_TD_3269_input_stringRowIDSubstitute, tbl_JOIN_LEFTSEMI_TD_2858_output, cfg_JOIN_LEFTSEMI_TD_2858_cmds, buftmp_h);
    krnlEngine krnl_JOIN_INNER_TD_3119;
    krnl_JOIN_INNER_TD_3119 = krnlEngine(program_h, q_h, "gqeJoin");
    krnl_JOIN_INNER_TD_3119.setup(tbl_JOIN_LEFTSEMI_TD_4303_output, tbl_Aggregate_TD_5342_output, tbl_JOIN_INNER_TD_3119_output, cfg_JOIN_INNER_TD_3119_cmds, buftmp_h);
    krnlEngine krnl_JOIN_LEFTSEMI_TD_4303;
    krnl_JOIN_LEFTSEMI_TD_4303 = krnlEngine(program_h, q_h, "gqeJoin");
    krnl_JOIN_LEFTSEMI_TD_4303.setup(tbl_Filter_TD_7153_output, tbl_SerializeFromObject_TD_587_input, tbl_JOIN_LEFTSEMI_TD_4303_output, cfg_JOIN_LEFTSEMI_TD_4303_cmds, buftmp_h);
    AggrKrnlEngine krnl_Aggregate_TD_5342;
    krnl_Aggregate_TD_5342 = AggrKrnlEngine(program_a, q_a, "gqeAggr");
    krnl_Aggregate_TD_5342.setup(tbl_JOIN_LEFTSEMI_TD_6448_output, tbl_Aggregate_TD_5342_output_preprocess, cfg_Aggregate_TD_5342_cmds, cfg_Aggregate_TD_5342_cmds_out, buftmp_a);
    krnlEngine krnl_JOIN_LEFTSEMI_TD_6448;
    krnl_JOIN_LEFTSEMI_TD_6448 = krnlEngine(program_h, q_h, "gqeJoin");
    krnl_JOIN_LEFTSEMI_TD_6448.setup(tbl_Filter_TD_7153_output, tbl_Filter_TD_760_output, tbl_JOIN_LEFTSEMI_TD_6448_output_preprocess, cfg_JOIN_LEFTSEMI_TD_6448_cmds, buftmp_h);
    // ************************** Transfer Engine *********************** // 
    transEngine trans_JOIN_INNER_TD_1206;
    trans_JOIN_INNER_TD_1206.setq(q_h);
    trans_JOIN_INNER_TD_1206.add(&(cfg_JOIN_INNER_TD_1206_cmds));
    transEngine trans_JOIN_INNER_TD_1206_out;
    trans_JOIN_INNER_TD_1206_out.setq(q_h);
    q_h.finish();
    transEngine trans_JOIN_LEFTSEMI_TD_2858;
    trans_JOIN_LEFTSEMI_TD_2858.setq(q_h);
    trans_JOIN_LEFTSEMI_TD_2858.add(&(cfg_JOIN_LEFTSEMI_TD_2858_cmds));
    trans_JOIN_LEFTSEMI_TD_2858.add(&(tbl_SerializeFromObject_TD_3269_input_stringRowIDSubstitute));
    q_h.finish();
    transEngine trans_JOIN_INNER_TD_3119;
    trans_JOIN_INNER_TD_3119.setq(q_h);
    trans_JOIN_INNER_TD_3119.add(&(cfg_JOIN_INNER_TD_3119_cmds));
    q_h.finish();
    transEngine trans_JOIN_LEFTSEMI_TD_4303;
    trans_JOIN_LEFTSEMI_TD_4303.setq(q_h);
    trans_JOIN_LEFTSEMI_TD_4303.add(&(cfg_JOIN_LEFTSEMI_TD_4303_cmds));
    trans_JOIN_LEFTSEMI_TD_4303.add(&(tbl_SerializeFromObject_TD_587_input));
    q_h.finish();
    transEngine trans_Aggregate_TD_5342;
    trans_Aggregate_TD_5342.setq(q_a);
    trans_Aggregate_TD_5342.add(&(cfg_Aggregate_TD_5342_cmds));
    transEngine trans_Aggregate_TD_5342_out;
    trans_Aggregate_TD_5342_out.setq(q_a);
    q_a.finish();
    transEngine trans_JOIN_LEFTSEMI_TD_6448;
    trans_JOIN_LEFTSEMI_TD_6448.setq(q_h);
    trans_JOIN_LEFTSEMI_TD_6448.add(&(cfg_JOIN_LEFTSEMI_TD_6448_cmds));
    transEngine trans_JOIN_LEFTSEMI_TD_6448_out;
    trans_JOIN_LEFTSEMI_TD_6448_out.setq(q_h);
    q_h.finish();
    // ****************************** Events **************************** // 
    std::vector<cl::Event> events_h2d_wr_JOIN_INNER_TD_1206;
    std::vector<cl::Event> events_d2h_rd_JOIN_INNER_TD_1206;
    std::vector<cl::Event> events_JOIN_INNER_TD_1206;
    events_h2d_wr_JOIN_INNER_TD_1206.resize(1);
    events_d2h_rd_JOIN_INNER_TD_1206.resize(1);
    events_JOIN_INNER_TD_1206.resize(1);
    std::vector<cl::Event> events_grp_JOIN_INNER_TD_1206;
    std::vector<cl::Event> prev_events_grp_JOIN_INNER_TD_1206;
    std::vector<cl::Event> events_h2d_wr_JOIN_LEFTSEMI_TD_2858;
    std::vector<cl::Event> events_d2h_rd_JOIN_LEFTSEMI_TD_2858;
    std::vector<cl::Event> events_JOIN_LEFTSEMI_TD_2858;
    events_h2d_wr_JOIN_LEFTSEMI_TD_2858.resize(1);
    events_d2h_rd_JOIN_LEFTSEMI_TD_2858.resize(1);
    events_JOIN_LEFTSEMI_TD_2858.resize(1);
    std::vector<cl::Event> events_grp_JOIN_LEFTSEMI_TD_2858;
    std::vector<cl::Event> prev_events_grp_JOIN_LEFTSEMI_TD_2858;
    std::vector<cl::Event> events_h2d_wr_JOIN_INNER_TD_3119;
    std::vector<cl::Event> events_d2h_rd_JOIN_INNER_TD_3119;
    std::vector<cl::Event> events_JOIN_INNER_TD_3119;
    events_h2d_wr_JOIN_INNER_TD_3119.resize(1);
    events_d2h_rd_JOIN_INNER_TD_3119.resize(1);
    events_JOIN_INNER_TD_3119.resize(1);
    std::vector<cl::Event> events_grp_JOIN_INNER_TD_3119;
    std::vector<cl::Event> prev_events_grp_JOIN_INNER_TD_3119;
    std::vector<cl::Event> events_h2d_wr_JOIN_LEFTSEMI_TD_4303;
    std::vector<cl::Event> events_d2h_rd_JOIN_LEFTSEMI_TD_4303;
    std::vector<cl::Event> events_JOIN_LEFTSEMI_TD_4303;
    events_h2d_wr_JOIN_LEFTSEMI_TD_4303.resize(1);
    events_d2h_rd_JOIN_LEFTSEMI_TD_4303.resize(1);
    events_JOIN_LEFTSEMI_TD_4303.resize(1);
    std::vector<cl::Event> events_grp_JOIN_LEFTSEMI_TD_4303;
    std::vector<cl::Event> prev_events_grp_JOIN_LEFTSEMI_TD_4303;
    std::vector<cl::Event> events_h2d_wr_Aggregate_TD_5342;
    std::vector<cl::Event> events_d2h_rd_Aggregate_TD_5342;
    std::vector<cl::Event> events_Aggregate_TD_5342;
    events_h2d_wr_Aggregate_TD_5342.resize(1);
    events_d2h_rd_Aggregate_TD_5342.resize(1);
    events_Aggregate_TD_5342.resize(1);
    std::vector<cl::Event> events_grp_Aggregate_TD_5342;
    std::vector<cl::Event> prev_events_grp_Aggregate_TD_5342;
    std::vector<cl::Event> events_h2d_wr_JOIN_LEFTSEMI_TD_6448;
    std::vector<cl::Event> events_d2h_rd_JOIN_LEFTSEMI_TD_6448;
    std::vector<cl::Event> events_JOIN_LEFTSEMI_TD_6448;
    events_h2d_wr_JOIN_LEFTSEMI_TD_6448.resize(1);
    events_d2h_rd_JOIN_LEFTSEMI_TD_6448.resize(1);
    events_JOIN_LEFTSEMI_TD_6448.resize(1);
    std::vector<cl::Event> events_grp_JOIN_LEFTSEMI_TD_6448;
    std::vector<cl::Event> prev_events_grp_JOIN_LEFTSEMI_TD_6448;
    // **************************** Operations ************************** // 
    struct timeval tv_r_s, tv_r_e; 
    gettimeofday(&tv_r_s, 0); 

    struct timeval tv_r_Filter_7_590_s, tv_r_Filter_7_590_e;
    gettimeofday(&tv_r_Filter_7_590_s, 0);
    SW_Filter_TD_7153(tbl_SerializeFromObject_TD_8916_input, tbl_Filter_TD_7153_output);
    gettimeofday(&tv_r_Filter_7_590_e, 0);

    struct timeval tv_r_Filter_7_4_s, tv_r_Filter_7_4_e;
    gettimeofday(&tv_r_Filter_7_4_s, 0);
    SW_Filter_TD_760(tbl_SerializeFromObject_TD_8615_input, tbl_Filter_TD_760_output);
    gettimeofday(&tv_r_Filter_7_4_e, 0);

    struct timeval tv_r_JOIN_LEFTSEMI_6_141_s, tv_r_JOIN_LEFTSEMI_6_141_e;
    gettimeofday(&tv_r_JOIN_LEFTSEMI_6_141_s, 0);
    trans_JOIN_LEFTSEMI_TD_6448.add(&(tbl_Filter_TD_760_output));
    trans_JOIN_LEFTSEMI_TD_6448.add(&(tbl_Filter_TD_7153_output));
    trans_JOIN_LEFTSEMI_TD_6448.host2dev(0, &(prev_events_grp_JOIN_LEFTSEMI_TD_6448), &(events_h2d_wr_JOIN_LEFTSEMI_TD_6448[0]));
    events_grp_JOIN_LEFTSEMI_TD_6448.push_back(events_h2d_wr_JOIN_LEFTSEMI_TD_6448[0]);
    krnl_JOIN_LEFTSEMI_TD_6448.run(0, &(events_grp_JOIN_LEFTSEMI_TD_6448), &(events_JOIN_LEFTSEMI_TD_6448[0]));
    
    trans_JOIN_LEFTSEMI_TD_6448_out.add(&(tbl_JOIN_LEFTSEMI_TD_6448_output_preprocess));
    trans_JOIN_LEFTSEMI_TD_6448_out.dev2host(0, &(events_JOIN_LEFTSEMI_TD_6448), &(events_d2h_rd_JOIN_LEFTSEMI_TD_6448[0]));
    q_h.flush();
    q_h.finish();
    WaitForEvents(events_d2h_rd_JOIN_LEFTSEMI_TD_6448);
    tbl_JOIN_LEFTSEMI_TD_6448_output_preprocess.copyTableData(&(tbl_JOIN_LEFTSEMI_TD_6448_output));
    gettimeofday(&tv_r_JOIN_LEFTSEMI_6_141_e, 0);

    struct timeval tv_r_Aggregate_5_565_s, tv_r_Aggregate_5_565_e;
    gettimeofday(&tv_r_Aggregate_5_565_s, 0);
    trans_Aggregate_TD_5342.add(&(tbl_JOIN_LEFTSEMI_TD_6448_output));
    trans_Aggregate_TD_5342.host2dev(0, &(prev_events_grp_Aggregate_TD_5342), &(events_h2d_wr_Aggregate_TD_5342[0]));
    events_grp_Aggregate_TD_5342.push_back(events_h2d_wr_Aggregate_TD_5342[0]);
    krnl_Aggregate_TD_5342.run(0, &(events_grp_Aggregate_TD_5342), &(events_Aggregate_TD_5342[0]));
    
    trans_Aggregate_TD_5342_out.add(&(tbl_Aggregate_TD_5342_output_preprocess));
    trans_Aggregate_TD_5342_out.dev2host(0, &(events_Aggregate_TD_5342), &(events_d2h_rd_Aggregate_TD_5342[0]));
    q_a.flush();
    q_a.finish();
    
    SW_Aggregate_TD_5342_consolidate(tbl_Aggregate_TD_5342_output_preprocess, tbl_Aggregate_TD_5342_output);
    gettimeofday(&tv_r_Aggregate_5_565_e, 0);

    struct timeval tv_r_JOIN_LEFTSEMI_4_157_s, tv_r_JOIN_LEFTSEMI_4_157_e;
    gettimeofday(&tv_r_JOIN_LEFTSEMI_4_157_s, 0);
    trans_JOIN_LEFTSEMI_TD_4303.add(&(tbl_Filter_TD_7153_output));
    trans_JOIN_LEFTSEMI_TD_4303.host2dev(0, &(prev_events_grp_JOIN_LEFTSEMI_TD_4303), &(events_h2d_wr_JOIN_LEFTSEMI_TD_4303[0]));
    events_grp_JOIN_LEFTSEMI_TD_4303.push_back(events_h2d_wr_JOIN_LEFTSEMI_TD_4303[0]);
    krnl_JOIN_LEFTSEMI_TD_4303.run(0, &(events_grp_JOIN_LEFTSEMI_TD_4303), &(events_JOIN_LEFTSEMI_TD_4303[0]));
    gettimeofday(&tv_r_JOIN_LEFTSEMI_4_157_e, 0);

    struct timeval tv_r_JOIN_INNER_3_746_s, tv_r_JOIN_INNER_3_746_e;
    gettimeofday(&tv_r_JOIN_INNER_3_746_s, 0);
    prev_events_grp_JOIN_INNER_TD_3119.push_back(events_h2d_wr_JOIN_LEFTSEMI_TD_4303[0]);
    trans_JOIN_INNER_TD_3119.add(&(tbl_Aggregate_TD_5342_output));
    trans_JOIN_INNER_TD_3119.host2dev(0, &(prev_events_grp_JOIN_INNER_TD_3119), &(events_h2d_wr_JOIN_INNER_TD_3119[0]));
    events_grp_JOIN_INNER_TD_3119.push_back(events_h2d_wr_JOIN_INNER_TD_3119[0]);
    events_grp_JOIN_INNER_TD_3119.push_back(events_JOIN_LEFTSEMI_TD_4303[0]);
    krnl_JOIN_INNER_TD_3119.run(0, &(events_grp_JOIN_INNER_TD_3119), &(events_JOIN_INNER_TD_3119[0]));
    gettimeofday(&tv_r_JOIN_INNER_3_746_e, 0);

    struct timeval tv_r_Filter_2_984_s, tv_r_Filter_2_984_e;
    gettimeofday(&tv_r_Filter_2_984_s, 0);
    SW_Filter_TD_2767(tbl_SerializeFromObject_TD_3798_input, tbl_Filter_TD_2767_output);
    gettimeofday(&tv_r_Filter_2_984_e, 0);

    struct timeval tv_r_JOIN_LEFTSEMI_2_746_s, tv_r_JOIN_LEFTSEMI_2_746_e;
    gettimeofday(&tv_r_JOIN_LEFTSEMI_2_746_s, 0);
    prev_events_grp_JOIN_LEFTSEMI_TD_2858.push_back(events_h2d_wr_JOIN_INNER_TD_3119[0]);
    trans_JOIN_LEFTSEMI_TD_2858.host2dev(0, &(prev_events_grp_JOIN_LEFTSEMI_TD_2858), &(events_h2d_wr_JOIN_LEFTSEMI_TD_2858[0]));
    events_grp_JOIN_LEFTSEMI_TD_2858.push_back(events_h2d_wr_JOIN_LEFTSEMI_TD_2858[0]);
    events_grp_JOIN_LEFTSEMI_TD_2858.push_back(events_JOIN_INNER_TD_3119[0]);
    krnl_JOIN_LEFTSEMI_TD_2858.run(0, &(events_grp_JOIN_LEFTSEMI_TD_2858), &(events_JOIN_LEFTSEMI_TD_2858[0]));
    gettimeofday(&tv_r_JOIN_LEFTSEMI_2_746_e, 0);

    struct timeval tv_r_JOIN_INNER_1_829_s, tv_r_JOIN_INNER_1_829_e;
    gettimeofday(&tv_r_JOIN_INNER_1_829_s, 0);
    prev_events_grp_JOIN_INNER_TD_1206.push_back(events_h2d_wr_JOIN_LEFTSEMI_TD_2858[0]);
    trans_JOIN_INNER_TD_1206.add(&(tbl_Filter_TD_2767_output));
    trans_JOIN_INNER_TD_1206.host2dev(0, &(prev_events_grp_JOIN_INNER_TD_1206), &(events_h2d_wr_JOIN_INNER_TD_1206[0]));
    events_grp_JOIN_INNER_TD_1206.push_back(events_h2d_wr_JOIN_INNER_TD_1206[0]);
    events_grp_JOIN_INNER_TD_1206.push_back(events_JOIN_LEFTSEMI_TD_2858[0]);
    krnl_JOIN_INNER_TD_1206.run(0, &(events_grp_JOIN_INNER_TD_1206), &(events_JOIN_INNER_TD_1206[0]));
    
    trans_JOIN_INNER_TD_1206_out.add(&(tbl_JOIN_INNER_TD_1206_output));
    trans_JOIN_INNER_TD_1206_out.dev2host(0, &(events_JOIN_INNER_TD_1206), &(events_d2h_rd_JOIN_INNER_TD_1206[0]));
    q_h.flush();
    q_h.finish();
    gettimeofday(&tv_r_JOIN_INNER_1_829_e, 0);

    struct timeval tv_r_Sort_0_62_s, tv_r_Sort_0_62_e;
    gettimeofday(&tv_r_Sort_0_62_s, 0);
    SW_Sort_TD_0293(tbl_JOIN_INNER_TD_1206_output, tbl_SerializeFromObject_TD_3269_input, tbl_SerializeFromObject_TD_3798_input, tbl_Sort_TD_0293_output);
    gettimeofday(&tv_r_Sort_0_62_e, 0);

    gettimeofday(&tv_r_e, 0); 
    // **************************** Print Execution Time ************************** // 
    std::cout << "Filter_7: " << tvdiff(&tv_r_Filter_7_590_s, &tv_r_Filter_7_590_e) / 1000.0 << " ms " 
     << "tbl_SerializeFromObject_TD_8916_input: " << tbl_SerializeFromObject_TD_8916_input.getNumRow() << " " << std::endl; 

    std::cout << "Filter_7: " << tvdiff(&tv_r_Filter_7_4_s, &tv_r_Filter_7_4_e) / 1000.0 << " ms " 
     << "tbl_SerializeFromObject_TD_8615_input: " << tbl_SerializeFromObject_TD_8615_input.getNumRow() << " " << std::endl; 

    std::cout << "JOIN_LEFTSEMI_6: " << tvdiff(&tv_r_JOIN_LEFTSEMI_6_141_s, &tv_r_JOIN_LEFTSEMI_6_141_e) / 1000.0 << " ms " 
     << "tbl_Filter_TD_760_output: " << tbl_Filter_TD_760_output.getNumRow() << " " << "tbl_Filter_TD_7153_output: " << tbl_Filter_TD_7153_output.getNumRow() << " " << std::endl; 

    std::cout << "Aggregate_5: " << tvdiff(&tv_r_Aggregate_5_565_s, &tv_r_Aggregate_5_565_e) / 1000.0 << " ms " 
     << "tbl_JOIN_LEFTSEMI_TD_6448_output: " << tbl_JOIN_LEFTSEMI_TD_6448_output.getNumRow() << " " << std::endl; 

    std::cout << "JOIN_LEFTSEMI_4: " << tvdiff(&tv_r_JOIN_LEFTSEMI_4_157_s, &tv_r_JOIN_LEFTSEMI_4_157_e) / 1000.0 << " ms " 
     << "tbl_SerializeFromObject_TD_587_input: " << tbl_SerializeFromObject_TD_587_input.getNumRow() << " " << "tbl_Filter_TD_7153_output: " << tbl_Filter_TD_7153_output.getNumRow() << " " << std::endl; 

    std::cout << "JOIN_INNER_3: " << tvdiff(&tv_r_JOIN_INNER_3_746_s, &tv_r_JOIN_INNER_3_746_e) / 1000.0 << " ms " 
     << "tbl_JOIN_LEFTSEMI_TD_4303_output: " << tbl_JOIN_LEFTSEMI_TD_4303_output.getNumRow() << " " << "tbl_Aggregate_TD_5342_output: " << tbl_Aggregate_TD_5342_output.getNumRow() << " " << std::endl; 

    std::cout << "Filter_2: " << tvdiff(&tv_r_Filter_2_984_s, &tv_r_Filter_2_984_e) / 1000.0 << " ms " 
     << "tbl_SerializeFromObject_TD_3798_input: " << tbl_SerializeFromObject_TD_3798_input.getNumRow() << " " << std::endl; 

    std::cout << "JOIN_LEFTSEMI_2: " << tvdiff(&tv_r_JOIN_LEFTSEMI_2_746_s, &tv_r_JOIN_LEFTSEMI_2_746_e) / 1000.0 << " ms " 
     << "tbl_SerializeFromObject_TD_3269_input_stringRowIDSubstitute: " << tbl_SerializeFromObject_TD_3269_input_stringRowIDSubstitute.getNumRow() << " " << "tbl_JOIN_INNER_TD_3119_output: " << tbl_JOIN_INNER_TD_3119_output.getNumRow() << " " << std::endl; 

    std::cout << "JOIN_INNER_1: " << tvdiff(&tv_r_JOIN_INNER_1_829_s, &tv_r_JOIN_INNER_1_829_e) / 1000.0 << " ms " 
     << "tbl_JOIN_LEFTSEMI_TD_2858_output: " << tbl_JOIN_LEFTSEMI_TD_2858_output.getNumRow() << " " << "tbl_Filter_TD_2767_output: " << tbl_Filter_TD_2767_output.getNumRow() << " " << std::endl; 

    std::cout << "Sort_0: " << tvdiff(&tv_r_Sort_0_62_s, &tv_r_Sort_0_62_e) / 1000.0 << " ms " 
     << "tbl_JOIN_INNER_TD_1206_output: " << tbl_JOIN_INNER_TD_1206_output.getNumRow() << " " << std::endl; 

    std::cout << std::endl << " Total execution time: " << tvdiff(&tv_r_s, &tv_r_e) / 1000 << " ms"; 

    std::cout << std::endl << " Spark elapsed time: " << 31.129906 * 1000 << "ms" << std::endl; 
    return 0; 
}
