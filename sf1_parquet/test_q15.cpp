// number of overlays (w/o fusion): 3 
// number of overlays (w/ fusion): 3 
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

#include "cfgFunc_q15.hpp" 
#include "q15.hpp" 

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
    std::cout << "NOTE:running query #15\n."; 
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
    Table tbl_Sort_TD_0662_output("tbl_Sort_TD_0662_output", 6100000, 5, "");
    tbl_Sort_TD_0662_output.allocateHost();
    Table tbl_JOIN_INNER_TD_1197_output("tbl_JOIN_INNER_TD_1197_output", -1, 5, "");
    tbl_JOIN_INNER_TD_1197_output.allocateHost();
    Table tbl_SerializeFromObject_TD_2111_input_stringRowIDSubstitute;
    tbl_SerializeFromObject_TD_2111_input_stringRowIDSubstitute = Table("supplier", supplier_n, 4, in_dir);
    tbl_SerializeFromObject_TD_2111_input_stringRowIDSubstitute.addCol("s_suppkey", 4);
    tbl_SerializeFromObject_TD_2111_input_stringRowIDSubstitute.addCol("s_name", 4, 1, 0);
    tbl_SerializeFromObject_TD_2111_input_stringRowIDSubstitute.addCol("s_address", 4, 1, 0);
    tbl_SerializeFromObject_TD_2111_input_stringRowIDSubstitute.addCol("s_phone", 4, 1, 0);
    tbl_SerializeFromObject_TD_2111_input_stringRowIDSubstitute.allocateHost();
    tbl_SerializeFromObject_TD_2111_input_stringRowIDSubstitute.loadHost();
    Table tbl_SerializeFromObject_TD_2111_input;
    tbl_SerializeFromObject_TD_2111_input = Table("supplier", supplier_n, 4, in_dir);
    tbl_SerializeFromObject_TD_2111_input.addCol("s_suppkey", 4);
    tbl_SerializeFromObject_TD_2111_input.addCol("s_name", TPCH_READ_S_NAME_LEN+1);
    tbl_SerializeFromObject_TD_2111_input.addCol("s_address", TPCH_READ_S_ADDR_MAX+1);
    tbl_SerializeFromObject_TD_2111_input.addCol("s_phone", TPCH_READ_PHONE_LEN+1);
    tbl_SerializeFromObject_TD_2111_input.allocateHost();
    tbl_SerializeFromObject_TD_2111_input.loadHost();
    Table tbl_Filter_TD_2251_output("tbl_Filter_TD_2251_output", 6100000, 2, "");
    tbl_Filter_TD_2251_output.allocateHost();
    Table tbl_Aggregate_TD_4461_output_preprocess("tbl_Aggregate_TD_4461_output_preprocess", -1, 16, "");
    tbl_Aggregate_TD_4461_output_preprocess.allocateHost();
    Table tbl_Aggregate_TD_4461_output("tbl_Aggregate_TD_4461_output", -1, 2, "");
    tbl_Aggregate_TD_4461_output.allocateHost();
    Table tbl_Aggregate_TD_4337_output("tbl_Aggregate_TD_4337_output", 6100000, 1, "");
    tbl_Aggregate_TD_4337_output.allocateHost();
    Table tbl_Aggregate_TD_5179_output_preprocess("tbl_Aggregate_TD_5179_output_preprocess", -1, 16, "");
    tbl_Aggregate_TD_5179_output_preprocess.allocateHost();
    Table tbl_Aggregate_TD_5179_output("tbl_Aggregate_TD_5179_output", -1, 1, "");
    tbl_Aggregate_TD_5179_output.allocateHost();
    Table tbl_Filter_TD_6694_output("tbl_Filter_TD_6694_output", 6100000, 3, "");
    tbl_Filter_TD_6694_output.allocateHost();
    Table tbl_SerializeFromObject_TD_72_input;
    tbl_SerializeFromObject_TD_72_input = Table("lineitem", lineitem_n, 4, in_dir);
    tbl_SerializeFromObject_TD_72_input.addCol("l_suppkey", 4);
    tbl_SerializeFromObject_TD_72_input.addCol("l_extendedprice", 4);
    tbl_SerializeFromObject_TD_72_input.addCol("l_discount", 4);
    tbl_SerializeFromObject_TD_72_input.addCol("l_shipdate", 4);
    tbl_SerializeFromObject_TD_72_input.allocateHost();
    tbl_SerializeFromObject_TD_72_input.loadHost();
    // ********************** Allocate Device Buffer ******************** // 
    tbl_JOIN_INNER_TD_1197_output.allocateDevBuffer(context_h, 32);
    tbl_SerializeFromObject_TD_2111_input_stringRowIDSubstitute.allocateDevBuffer(context_h, 32);
    tbl_Filter_TD_2251_output.allocateDevBuffer(context_h, 32);
    tbl_Aggregate_TD_4461_output_preprocess.allocateDevBuffer(context_a, 33);
    tbl_Aggregate_TD_5179_output_preprocess.allocateDevBuffer(context_a, 33);
    tbl_Filter_TD_6694_output.allocateDevBuffer(context_a, 32);
    // ****************************** Config **************************** // 
    cfgCmd cfg_JOIN_INNER_TD_1197_cmds;
    cfg_JOIN_INNER_TD_1197_cmds.allocateHost();
    get_cfg_dat_JOIN_INNER_TD_1197_gqe_join (cfg_JOIN_INNER_TD_1197_cmds.cmd);
    cfg_JOIN_INNER_TD_1197_cmds.allocateDevBuffer(context_h, 32);
    AggrCfgCmd cfg_Aggregate_TD_4461_cmds;
    cfg_Aggregate_TD_4461_cmds.allocateHost();
    get_cfg_dat_Aggregate_TD_4461_gqe_aggr(cfg_Aggregate_TD_4461_cmds.cmd);
    cfg_Aggregate_TD_4461_cmds.allocateDevBuffer(context_a, 32);
    AggrCfgCmd cfg_Aggregate_TD_4461_cmds_out;
    cfg_Aggregate_TD_4461_cmds_out.allocateHost();
    cfg_Aggregate_TD_4461_cmds_out.allocateDevBuffer(context_a, 33);
    AggrCfgCmd cfg_Aggregate_TD_5179_cmds;
    cfg_Aggregate_TD_5179_cmds.allocateHost();
    get_cfg_dat_Aggregate_TD_5179_gqe_aggr(cfg_Aggregate_TD_5179_cmds.cmd);
    cfg_Aggregate_TD_5179_cmds.allocateDevBuffer(context_a, 32);
    AggrCfgCmd cfg_Aggregate_TD_5179_cmds_out;
    cfg_Aggregate_TD_5179_cmds_out.allocateHost();
    cfg_Aggregate_TD_5179_cmds_out.allocateDevBuffer(context_a, 33);
    // *************************** Kernel Setup ************************* // 
    bufferTmp buftmp_h(context_h); 
    buftmp_h.initBuffer(q_h); 
    AggrBufferTmp buftmp_a(context_a); 
    buftmp_a.BufferInitial(q_a); 
    std::cout << std::endl; 
    krnlEngine krnl_JOIN_INNER_TD_1197;
    krnl_JOIN_INNER_TD_1197 = krnlEngine(program_h, q_h, "gqeJoin");
    krnl_JOIN_INNER_TD_1197.setup(tbl_SerializeFromObject_TD_2111_input_stringRowIDSubstitute, tbl_Filter_TD_2251_output, tbl_JOIN_INNER_TD_1197_output, cfg_JOIN_INNER_TD_1197_cmds, buftmp_h);
    AggrKrnlEngine krnl_Aggregate_TD_4461;
    krnl_Aggregate_TD_4461 = AggrKrnlEngine(program_a, q_a, "gqeAggr");
    krnl_Aggregate_TD_4461.setup(tbl_Filter_TD_6694_output, tbl_Aggregate_TD_4461_output_preprocess, cfg_Aggregate_TD_4461_cmds, cfg_Aggregate_TD_4461_cmds_out, buftmp_a);
    AggrKrnlEngine krnl_Aggregate_TD_5179;
    krnl_Aggregate_TD_5179 = AggrKrnlEngine(program_a, q_a, "gqeAggr");
    krnl_Aggregate_TD_5179.setup(tbl_Filter_TD_6694_output, tbl_Aggregate_TD_5179_output_preprocess, cfg_Aggregate_TD_5179_cmds, cfg_Aggregate_TD_5179_cmds_out, buftmp_a);
    // ************************** Transfer Engine *********************** // 
    transEngine trans_JOIN_INNER_TD_1197;
    trans_JOIN_INNER_TD_1197.setq(q_h);
    trans_JOIN_INNER_TD_1197.add(&(cfg_JOIN_INNER_TD_1197_cmds));
    trans_JOIN_INNER_TD_1197.add(&(tbl_SerializeFromObject_TD_2111_input_stringRowIDSubstitute));
    transEngine trans_JOIN_INNER_TD_1197_out;
    trans_JOIN_INNER_TD_1197_out.setq(q_h);
    q_h.finish();
    transEngine trans_Aggregate_TD_4461;
    trans_Aggregate_TD_4461.setq(q_a);
    trans_Aggregate_TD_4461.add(&(cfg_Aggregate_TD_4461_cmds));
    transEngine trans_Aggregate_TD_4461_out;
    trans_Aggregate_TD_4461_out.setq(q_a);
    q_a.finish();
    transEngine trans_Aggregate_TD_5179;
    trans_Aggregate_TD_5179.setq(q_a);
    trans_Aggregate_TD_5179.add(&(cfg_Aggregate_TD_5179_cmds));
    transEngine trans_Aggregate_TD_5179_out;
    trans_Aggregate_TD_5179_out.setq(q_a);
    q_a.finish();
    // ****************************** Events **************************** // 
    std::vector<cl::Event> events_h2d_wr_JOIN_INNER_TD_1197;
    std::vector<cl::Event> events_d2h_rd_JOIN_INNER_TD_1197;
    std::vector<cl::Event> events_JOIN_INNER_TD_1197;
    events_h2d_wr_JOIN_INNER_TD_1197.resize(1);
    events_d2h_rd_JOIN_INNER_TD_1197.resize(1);
    events_JOIN_INNER_TD_1197.resize(1);
    std::vector<cl::Event> events_grp_JOIN_INNER_TD_1197;
    std::vector<cl::Event> prev_events_grp_JOIN_INNER_TD_1197;
    std::vector<cl::Event> events_h2d_wr_Aggregate_TD_4461;
    std::vector<cl::Event> events_d2h_rd_Aggregate_TD_4461;
    std::vector<cl::Event> events_Aggregate_TD_4461;
    events_h2d_wr_Aggregate_TD_4461.resize(1);
    events_d2h_rd_Aggregate_TD_4461.resize(1);
    events_Aggregate_TD_4461.resize(1);
    std::vector<cl::Event> events_grp_Aggregate_TD_4461;
    std::vector<cl::Event> prev_events_grp_Aggregate_TD_4461;
    std::vector<cl::Event> events_h2d_wr_Aggregate_TD_5179;
    std::vector<cl::Event> events_d2h_rd_Aggregate_TD_5179;
    std::vector<cl::Event> events_Aggregate_TD_5179;
    events_h2d_wr_Aggregate_TD_5179.resize(1);
    events_d2h_rd_Aggregate_TD_5179.resize(1);
    events_Aggregate_TD_5179.resize(1);
    std::vector<cl::Event> events_grp_Aggregate_TD_5179;
    std::vector<cl::Event> prev_events_grp_Aggregate_TD_5179;
    // **************************** Operations ************************** // 
    struct timeval tv_r_s, tv_r_e; 
    gettimeofday(&tv_r_s, 0); 

    struct timeval tv_r_Filter_6_528_s, tv_r_Filter_6_528_e;
    gettimeofday(&tv_r_Filter_6_528_s, 0);
    SW_Filter_TD_6694(tbl_SerializeFromObject_TD_72_input, tbl_Filter_TD_6694_output);
    gettimeofday(&tv_r_Filter_6_528_e, 0);

    struct timeval tv_r_Aggregate_5_299_s, tv_r_Aggregate_5_299_e;
    gettimeofday(&tv_r_Aggregate_5_299_s, 0);
    trans_Aggregate_TD_5179.add(&(tbl_Filter_TD_6694_output));
    trans_Aggregate_TD_5179.host2dev(0, &(prev_events_grp_Aggregate_TD_5179), &(events_h2d_wr_Aggregate_TD_5179[0]));
    events_grp_Aggregate_TD_5179.push_back(events_h2d_wr_Aggregate_TD_5179[0]);
    krnl_Aggregate_TD_5179.run(0, &(events_grp_Aggregate_TD_5179), &(events_Aggregate_TD_5179[0]));
    
    trans_Aggregate_TD_5179_out.add(&(tbl_Aggregate_TD_5179_output_preprocess));
    trans_Aggregate_TD_5179_out.dev2host(0, &(events_Aggregate_TD_5179), &(events_d2h_rd_Aggregate_TD_5179[0]));
    q_a.flush();
    q_a.finish();
    
    SW_Aggregate_TD_5179_consolidate(tbl_Aggregate_TD_5179_output_preprocess, tbl_Aggregate_TD_5179_output);
    gettimeofday(&tv_r_Aggregate_5_299_e, 0);

    struct timeval tv_r_Aggregate_4_607_s, tv_r_Aggregate_4_607_e;
    gettimeofday(&tv_r_Aggregate_4_607_s, 0);
    SW_Aggregate_TD_4337(tbl_Aggregate_TD_5179_output, tbl_Aggregate_TD_4337_output);
    gettimeofday(&tv_r_Aggregate_4_607_e, 0);

    struct timeval tv_r_Aggregate_4_439_s, tv_r_Aggregate_4_439_e;
    gettimeofday(&tv_r_Aggregate_4_439_s, 0);
    trans_Aggregate_TD_4461.add(&(tbl_Filter_TD_6694_output));
    trans_Aggregate_TD_4461.host2dev(0, &(prev_events_grp_Aggregate_TD_4461), &(events_h2d_wr_Aggregate_TD_4461[0]));
    events_grp_Aggregate_TD_4461.push_back(events_h2d_wr_Aggregate_TD_4461[0]);
    krnl_Aggregate_TD_4461.run(0, &(events_grp_Aggregate_TD_4461), &(events_Aggregate_TD_4461[0]));
    
    trans_Aggregate_TD_4461_out.add(&(tbl_Aggregate_TD_4461_output_preprocess));
    trans_Aggregate_TD_4461_out.dev2host(0, &(events_Aggregate_TD_4461), &(events_d2h_rd_Aggregate_TD_4461[0]));
    q_a.flush();
    q_a.finish();
    
    SW_Aggregate_TD_4461_consolidate(tbl_Aggregate_TD_4461_output_preprocess, tbl_Aggregate_TD_4461_output);
    gettimeofday(&tv_r_Aggregate_4_439_e, 0);

    struct timeval tv_r_Filter_2_603_s, tv_r_Filter_2_603_e;
    gettimeofday(&tv_r_Filter_2_603_s, 0);
    SW_Filter_TD_2251(tbl_Aggregate_TD_4461_output, tbl_Aggregate_TD_4337_output, tbl_Filter_TD_2251_output);
    gettimeofday(&tv_r_Filter_2_603_e, 0);

    struct timeval tv_r_JOIN_INNER_1_140_s, tv_r_JOIN_INNER_1_140_e;
    gettimeofday(&tv_r_JOIN_INNER_1_140_s, 0);
    trans_JOIN_INNER_TD_1197.add(&(tbl_Filter_TD_2251_output));
    trans_JOIN_INNER_TD_1197.host2dev(0, &(prev_events_grp_JOIN_INNER_TD_1197), &(events_h2d_wr_JOIN_INNER_TD_1197[0]));
    events_grp_JOIN_INNER_TD_1197.push_back(events_h2d_wr_JOIN_INNER_TD_1197[0]);
    krnl_JOIN_INNER_TD_1197.run(0, &(events_grp_JOIN_INNER_TD_1197), &(events_JOIN_INNER_TD_1197[0]));
    
    trans_JOIN_INNER_TD_1197_out.add(&(tbl_JOIN_INNER_TD_1197_output));
    trans_JOIN_INNER_TD_1197_out.dev2host(0, &(events_JOIN_INNER_TD_1197), &(events_d2h_rd_JOIN_INNER_TD_1197[0]));
    q_h.flush();
    q_h.finish();
    gettimeofday(&tv_r_JOIN_INNER_1_140_e, 0);

    struct timeval tv_r_Sort_0_260_s, tv_r_Sort_0_260_e;
    gettimeofday(&tv_r_Sort_0_260_s, 0);
    SW_Sort_TD_0662(tbl_JOIN_INNER_TD_1197_output, tbl_SerializeFromObject_TD_2111_input, tbl_Sort_TD_0662_output);
    gettimeofday(&tv_r_Sort_0_260_e, 0);

    gettimeofday(&tv_r_e, 0); 
    // **************************** Print Execution Time ************************** // 
    std::cout << "Filter_6: " << tvdiff(&tv_r_Filter_6_528_s, &tv_r_Filter_6_528_e) / 1000.0 << " ms " 
     << "tbl_SerializeFromObject_TD_72_input: " << tbl_SerializeFromObject_TD_72_input.getNumRow() << " " << std::endl; 

    std::cout << "Aggregate_5: " << tvdiff(&tv_r_Aggregate_5_299_s, &tv_r_Aggregate_5_299_e) / 1000.0 << " ms " 
     << "tbl_Filter_TD_6694_output: " << tbl_Filter_TD_6694_output.getNumRow() << " " << std::endl; 

    std::cout << "Aggregate_4: " << tvdiff(&tv_r_Aggregate_4_607_s, &tv_r_Aggregate_4_607_e) / 1000.0 << " ms " 
     << "tbl_Aggregate_TD_5179_output: " << tbl_Aggregate_TD_5179_output.getNumRow() << " " << std::endl; 

    std::cout << "Aggregate_4: " << tvdiff(&tv_r_Aggregate_4_439_s, &tv_r_Aggregate_4_439_e) / 1000.0 << " ms " 
     << "tbl_Filter_TD_6694_output: " << tbl_Filter_TD_6694_output.getNumRow() << " " << std::endl; 

    std::cout << "Filter_2: " << tvdiff(&tv_r_Filter_2_603_s, &tv_r_Filter_2_603_e) / 1000.0 << " ms " 
     << "tbl_Aggregate_TD_4461_output: " << tbl_Aggregate_TD_4461_output.getNumRow() << " " << "tbl_Aggregate_TD_4337_output: " << tbl_Aggregate_TD_4337_output.getNumRow() << " " << std::endl; 

    std::cout << "JOIN_INNER_1: " << tvdiff(&tv_r_JOIN_INNER_1_140_s, &tv_r_JOIN_INNER_1_140_e) / 1000.0 << " ms " 
     << "tbl_SerializeFromObject_TD_2111_input_stringRowIDSubstitute: " << tbl_SerializeFromObject_TD_2111_input_stringRowIDSubstitute.getNumRow() << " " << "tbl_Filter_TD_2251_output: " << tbl_Filter_TD_2251_output.getNumRow() << " " << std::endl; 

    std::cout << "Sort_0: " << tvdiff(&tv_r_Sort_0_260_s, &tv_r_Sort_0_260_e) / 1000.0 << " ms " 
     << "tbl_JOIN_INNER_TD_1197_output: " << tbl_JOIN_INNER_TD_1197_output.getNumRow() << " " << std::endl; 

    std::cout << std::endl << " Total execution time: " << tvdiff(&tv_r_s, &tv_r_e) / 1000 << " ms"; 

    std::cout << std::endl << " Spark elapsed time: " << 26.591303 * 1000 << "ms" << std::endl; 
    return 0; 
}
