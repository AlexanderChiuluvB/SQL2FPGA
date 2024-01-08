// number of overlays (w/o fusion): 7 
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

#include "cfgFunc_q18.hpp" 
#include "q18.hpp" 

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
    std::cout << "NOTE:running query #18\n."; 
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
    Table tbl_Sort_TD_0643_output("tbl_Sort_TD_0643_output", 6100000, 6, "");
    tbl_Sort_TD_0643_output.allocateHost();
    Table tbl_Aggregate_TD_1818_output("tbl_Aggregate_TD_1818_output", 6100000, 6, "");
    tbl_Aggregate_TD_1818_output.allocateHost();
    Table tbl_JOIN_INNER_TD_2361_output("tbl_JOIN_INNER_TD_2361_output", 100, 6, "");
    tbl_JOIN_INNER_TD_2361_output.allocateHost();
    Table tbl_JOIN_LEFTSEMI_TD_587_output("tbl_JOIN_LEFTSEMI_TD_587_output", 6100000, 4, "");
    tbl_JOIN_LEFTSEMI_TD_587_output.allocateHost();
    Table tbl_JOIN_LEFTSEMI_TD_448_output("tbl_JOIN_LEFTSEMI_TD_448_output", 6100000, 2, "");
    tbl_JOIN_LEFTSEMI_TD_448_output.allocateHost();
    Table tbl_SerializeFromObject_TD_7950_input;
    tbl_SerializeFromObject_TD_7950_input = Table("orders", orders_n, 4, in_dir);
    tbl_SerializeFromObject_TD_7950_input.addCol("o_orderkey", 4);
    tbl_SerializeFromObject_TD_7950_input.addCol("o_custkey", 4);
    tbl_SerializeFromObject_TD_7950_input.addCol("o_totalprice", 4);
    tbl_SerializeFromObject_TD_7950_input.addCol("o_orderdate", 4);
    tbl_SerializeFromObject_TD_7950_input.allocateHost();
    tbl_SerializeFromObject_TD_7950_input.loadHost();
    Table tbl_SerializeFromObject_TD_6400_input;
    tbl_SerializeFromObject_TD_6400_input = Table("lineitem", lineitem_n, 2, in_dir);
    tbl_SerializeFromObject_TD_6400_input.addCol("l_orderkey", 4);
    tbl_SerializeFromObject_TD_6400_input.addCol("l_quantity", 4);
    tbl_SerializeFromObject_TD_6400_input.allocateHost();
    tbl_SerializeFromObject_TD_6400_input.loadHost();
    Table tbl_Filter_TD_579_output("tbl_Filter_TD_579_output", 6100000, 1, "");
    tbl_Filter_TD_579_output.allocateHost();
    Table tbl_Aggregate_TD_663_output_preprocess("tbl_Aggregate_TD_663_output_preprocess", 3000000, 16, "");
    tbl_Aggregate_TD_663_output_preprocess.allocateHost();
    Table tbl_Aggregate_TD_663_output("tbl_Aggregate_TD_663_output", 3000000, 2, "");
    tbl_Aggregate_TD_663_output.allocateHost();
    Table tbl_SerializeFromObject_TD_8989_input;
    tbl_SerializeFromObject_TD_8989_input = Table("lineitem", lineitem_n, 2, in_dir);
    tbl_SerializeFromObject_TD_8989_input.addCol("l_orderkey", 4);
    tbl_SerializeFromObject_TD_8989_input.addCol("l_quantity", 4);
    tbl_SerializeFromObject_TD_8989_input.allocateHost();
    tbl_SerializeFromObject_TD_8989_input.loadHost();
    // ********************** Allocate Device Buffer ******************** // 
    tbl_JOIN_INNER_TD_2361_output.allocateDevBuffer(context_h, 32);
    tbl_JOIN_LEFTSEMI_TD_587_output.allocateDevBuffer(context_h, 32);
    tbl_JOIN_LEFTSEMI_TD_448_output.allocateDevBuffer(context_h, 32);
    tbl_Aggregate_TD_663_output_preprocess.allocateDevBuffer(context_a, 33);
    tbl_SerializeFromObject_TD_8989_input.allocateDevBuffer(context_a, 32);
    // ****************************** Config **************************** // 
    cfgCmd cfg_JOIN_INNER_TD_2361_cmds;
    cfg_JOIN_INNER_TD_2361_cmds.allocateHost();
    get_cfg_dat_JOIN_INNER_TD_2361_gqe_join (cfg_JOIN_INNER_TD_2361_cmds.cmd);
    cfg_JOIN_INNER_TD_2361_cmds.allocateDevBuffer(context_h, 32);
    AggrCfgCmd cfg_Aggregate_TD_663_cmds;
    cfg_Aggregate_TD_663_cmds.allocateHost();
    get_cfg_dat_Aggregate_TD_663_gqe_aggr(cfg_Aggregate_TD_663_cmds.cmd);
    cfg_Aggregate_TD_663_cmds.allocateDevBuffer(context_a, 32);
    AggrCfgCmd cfg_Aggregate_TD_663_cmds_out;
    cfg_Aggregate_TD_663_cmds_out.allocateHost();
    cfg_Aggregate_TD_663_cmds_out.allocateDevBuffer(context_a, 33);
    // *************************** Kernel Setup ************************* // 
    bufferTmp buftmp_h(context_h); 
    buftmp_h.initBuffer(q_h); 
    AggrBufferTmp buftmp_a(context_a); 
    buftmp_a.BufferInitial(q_a); 
    std::cout << std::endl; 
    krnlEngine krnl_JOIN_INNER_TD_2361;
    krnl_JOIN_INNER_TD_2361 = krnlEngine(program_h, q_h, "gqeJoin");
    krnl_JOIN_INNER_TD_2361.setup(tbl_JOIN_LEFTSEMI_TD_587_output, tbl_JOIN_LEFTSEMI_TD_448_output, tbl_JOIN_INNER_TD_2361_output, cfg_JOIN_INNER_TD_2361_cmds, buftmp_h);
    AggrKrnlEngine krnl_Aggregate_TD_663;
    krnl_Aggregate_TD_663 = AggrKrnlEngine(program_a, q_a, "gqeAggr");
    krnl_Aggregate_TD_663.setup(tbl_SerializeFromObject_TD_8989_input, tbl_Aggregate_TD_663_output_preprocess, cfg_Aggregate_TD_663_cmds, cfg_Aggregate_TD_663_cmds_out, buftmp_a);
    // ************************** Transfer Engine *********************** // 
    transEngine trans_JOIN_INNER_TD_2361;
    trans_JOIN_INNER_TD_2361.setq(q_h);
    trans_JOIN_INNER_TD_2361.add(&(cfg_JOIN_INNER_TD_2361_cmds));
    transEngine trans_JOIN_INNER_TD_2361_out;
    trans_JOIN_INNER_TD_2361_out.setq(q_h);
    q_h.finish();
    transEngine trans_Aggregate_TD_663;
    trans_Aggregate_TD_663.setq(q_a);
    trans_Aggregate_TD_663.add(&(cfg_Aggregate_TD_663_cmds));
    trans_Aggregate_TD_663.add(&(tbl_SerializeFromObject_TD_8989_input));
    transEngine trans_Aggregate_TD_663_out;
    trans_Aggregate_TD_663_out.setq(q_a);
    q_a.finish();
    // ****************************** Events **************************** // 
    std::vector<cl::Event> events_h2d_wr_JOIN_INNER_TD_2361;
    std::vector<cl::Event> events_d2h_rd_JOIN_INNER_TD_2361;
    std::vector<cl::Event> events_JOIN_INNER_TD_2361;
    events_h2d_wr_JOIN_INNER_TD_2361.resize(1);
    events_d2h_rd_JOIN_INNER_TD_2361.resize(1);
    events_JOIN_INNER_TD_2361.resize(1);
    std::vector<cl::Event> events_grp_JOIN_INNER_TD_2361;
    std::vector<cl::Event> prev_events_grp_JOIN_INNER_TD_2361;
    std::vector<cl::Event> events_h2d_wr_Aggregate_TD_663;
    std::vector<cl::Event> events_d2h_rd_Aggregate_TD_663;
    std::vector<cl::Event> events_Aggregate_TD_663;
    events_h2d_wr_Aggregate_TD_663.resize(1);
    events_d2h_rd_Aggregate_TD_663.resize(1);
    events_Aggregate_TD_663.resize(1);
    std::vector<cl::Event> events_grp_Aggregate_TD_663;
    std::vector<cl::Event> prev_events_grp_Aggregate_TD_663;
    // **************************** Operations ************************** // 
    struct timeval tv_r_s, tv_r_e; 
    gettimeofday(&tv_r_s, 0); 

    struct timeval tv_r_Aggregate_6_969_s, tv_r_Aggregate_6_969_e;
    gettimeofday(&tv_r_Aggregate_6_969_s, 0);
    trans_Aggregate_TD_663.host2dev(0, &(prev_events_grp_Aggregate_TD_663), &(events_h2d_wr_Aggregate_TD_663[0]));
    events_grp_Aggregate_TD_663.push_back(events_h2d_wr_Aggregate_TD_663[0]);
    krnl_Aggregate_TD_663.run(0, &(events_grp_Aggregate_TD_663), &(events_Aggregate_TD_663[0]));
    
    trans_Aggregate_TD_663_out.add(&(tbl_Aggregate_TD_663_output_preprocess));
    trans_Aggregate_TD_663_out.dev2host(0, &(events_Aggregate_TD_663), &(events_d2h_rd_Aggregate_TD_663[0]));
    q_a.flush();
    q_a.finish();
    
    SW_Aggregate_TD_663_consolidate(tbl_Aggregate_TD_663_output_preprocess, tbl_Aggregate_TD_663_output);
    gettimeofday(&tv_r_Aggregate_6_969_e, 0);

    struct timeval tv_r_Filter_5_464_s, tv_r_Filter_5_464_e;
    gettimeofday(&tv_r_Filter_5_464_s, 0);
    SW_Filter_TD_579(tbl_Aggregate_TD_663_output, tbl_Filter_TD_579_output);
    gettimeofday(&tv_r_Filter_5_464_e, 0);

    struct timeval tv_r_JOIN_LEFTSEMI_4_559_s, tv_r_JOIN_LEFTSEMI_4_559_e;
    gettimeofday(&tv_r_JOIN_LEFTSEMI_4_559_s, 0);
    SW_JOIN_LEFTSEMI_TD_448(tbl_SerializeFromObject_TD_6400_input, tbl_Filter_TD_579_output, tbl_JOIN_LEFTSEMI_TD_448_output);
    gettimeofday(&tv_r_JOIN_LEFTSEMI_4_559_e, 0);

    struct timeval tv_r_JOIN_LEFTSEMI_5_621_s, tv_r_JOIN_LEFTSEMI_5_621_e;
    gettimeofday(&tv_r_JOIN_LEFTSEMI_5_621_s, 0);
    SW_JOIN_LEFTSEMI_TD_587(tbl_SerializeFromObject_TD_7950_input, tbl_Filter_TD_579_output, tbl_JOIN_LEFTSEMI_TD_587_output);
    gettimeofday(&tv_r_JOIN_LEFTSEMI_5_621_e, 0);

    struct timeval tv_r_JOIN_INNER_2_183_s, tv_r_JOIN_INNER_2_183_e;
    gettimeofday(&tv_r_JOIN_INNER_2_183_s, 0);
    trans_JOIN_INNER_TD_2361.add(&(tbl_JOIN_LEFTSEMI_TD_587_output));
    trans_JOIN_INNER_TD_2361.add(&(tbl_JOIN_LEFTSEMI_TD_448_output));
    trans_JOIN_INNER_TD_2361.host2dev(0, &(prev_events_grp_JOIN_INNER_TD_2361), &(events_h2d_wr_JOIN_INNER_TD_2361[0]));
    events_grp_JOIN_INNER_TD_2361.push_back(events_h2d_wr_JOIN_INNER_TD_2361[0]);
    krnl_JOIN_INNER_TD_2361.run(0, &(events_grp_JOIN_INNER_TD_2361), &(events_JOIN_INNER_TD_2361[0]));
    
    trans_JOIN_INNER_TD_2361_out.add(&(tbl_JOIN_INNER_TD_2361_output));
    trans_JOIN_INNER_TD_2361_out.dev2host(0, &(events_JOIN_INNER_TD_2361), &(events_d2h_rd_JOIN_INNER_TD_2361[0]));
    q_h.flush();
    q_h.finish();
    gettimeofday(&tv_r_JOIN_INNER_2_183_e, 0);

    struct timeval tv_r_Aggregate_1_993_s, tv_r_Aggregate_1_993_e;
    gettimeofday(&tv_r_Aggregate_1_993_s, 0);
    SW_Aggregate_TD_1818(tbl_JOIN_INNER_TD_2361_output, tbl_Aggregate_TD_1818_output);
    gettimeofday(&tv_r_Aggregate_1_993_e, 0);

    struct timeval tv_r_Sort_0_918_s, tv_r_Sort_0_918_e;
    gettimeofday(&tv_r_Sort_0_918_s, 0);
    SW_Sort_TD_0643(tbl_Aggregate_TD_1818_output, tbl_Sort_TD_0643_output);
    gettimeofday(&tv_r_Sort_0_918_e, 0);

    gettimeofday(&tv_r_e, 0); 
    // **************************** Print Execution Time ************************** // 
    std::cout << "Aggregate_6: " << tvdiff(&tv_r_Aggregate_6_969_s, &tv_r_Aggregate_6_969_e) / 1000.0 << " ms " 
     << "tbl_SerializeFromObject_TD_8989_input: " << tbl_SerializeFromObject_TD_8989_input.getNumRow() << " " << std::endl; 

    std::cout << "Filter_5: " << tvdiff(&tv_r_Filter_5_464_s, &tv_r_Filter_5_464_e) / 1000.0 << " ms " 
     << "tbl_Aggregate_TD_663_output: " << tbl_Aggregate_TD_663_output.getNumRow() << " " << std::endl; 

    std::cout << "JOIN_LEFTSEMI_4: " << tvdiff(&tv_r_JOIN_LEFTSEMI_4_559_s, &tv_r_JOIN_LEFTSEMI_4_559_e) / 1000.0 << " ms " 
     << "tbl_SerializeFromObject_TD_6400_input: " << tbl_SerializeFromObject_TD_6400_input.getNumRow() << " " << "tbl_Filter_TD_579_output: " << tbl_Filter_TD_579_output.getNumRow() << " " << std::endl; 

    std::cout << "JOIN_LEFTSEMI_5: " << tvdiff(&tv_r_JOIN_LEFTSEMI_5_621_s, &tv_r_JOIN_LEFTSEMI_5_621_e) / 1000.0 << " ms " 
     << "tbl_SerializeFromObject_TD_7950_input: " << tbl_SerializeFromObject_TD_7950_input.getNumRow() << " " << "tbl_Filter_TD_579_output: " << tbl_Filter_TD_579_output.getNumRow() << " " << std::endl; 

    std::cout << "JOIN_INNER_2: " << tvdiff(&tv_r_JOIN_INNER_2_183_s, &tv_r_JOIN_INNER_2_183_e) / 1000.0 << " ms " 
     << "tbl_JOIN_LEFTSEMI_TD_587_output: " << tbl_JOIN_LEFTSEMI_TD_587_output.getNumRow() << " " << "tbl_JOIN_LEFTSEMI_TD_448_output: " << tbl_JOIN_LEFTSEMI_TD_448_output.getNumRow() << " " << std::endl; 

    std::cout << "Aggregate_1: " << tvdiff(&tv_r_Aggregate_1_993_s, &tv_r_Aggregate_1_993_e) / 1000.0 << " ms " 
     << "tbl_JOIN_INNER_TD_2361_output: " << tbl_JOIN_INNER_TD_2361_output.getNumRow() << " " << std::endl; 

    std::cout << "Sort_0: " << tvdiff(&tv_r_Sort_0_918_s, &tv_r_Sort_0_918_e) / 1000.0 << " ms " 
     << "tbl_Aggregate_TD_1818_output: " << tbl_Aggregate_TD_1818_output.getNumRow() << " " << std::endl; 

    std::cout << std::endl << " Total execution time: " << tvdiff(&tv_r_s, &tv_r_e) / 1000 << " ms"; 

    std::cout << std::endl << " Spark elapsed time: " << 50.78087 * 1000 << "ms" << std::endl; 
    return 0; 
}
