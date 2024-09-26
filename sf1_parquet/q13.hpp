#include <regex> 
#include <stdint.h> 

void SW_Filter_TD_4206(Table &tbl_SerializeFromObject_TD_5927_input, Table &tbl_Filter_TD_4206_output) {
    // StringRowIDSubstitution: false StringRowIDBackSubstitution: false
    // Supported operation: Filter
    // Operation: ListBuffer((isnotnull(o_comment#235) AND NOT o_comment#235 LIKE %unusual%deposits%))
    // Input: ListBuffer(o_orderkey#227, o_custkey#228, o_comment#235)
    // Output: ListBuffer(o_orderkey#227, o_custkey#228)
    int r = 0;
    int nrow1 = tbl_SerializeFromObject_TD_5927_input.getNumRow();
    for (int i = 0; i < nrow1; i++) {
        std::array<char, TPCH_READ_REGION_LEN + 1> _o_comment235 = tbl_SerializeFromObject_TD_5927_input.getcharN<char, TPCH_READ_REGION_LEN + 1>(i, 2);
        struct custom_func {
                bool strm_pattern(std::string sub1, std::string sub2, std::string s, int len = 7) {
                    std::string::size_type spe_f = s.find(sub1);
                    std::string::size_type c_f = 0;
                    while (spe_f != std::string::npos) {
                        c_f += (spe_f + len);
                        std::string sub_s = s.substr(c_f);
                        if (sub_s.find(sub2) != std::string::npos) return true;
                        spe_f = sub_s.find(sub1);
                    }
                    return false;
                }
        }custom_func_obj;
        if ((1) && !(custom_func_obj.strm_pattern("unusual", "deposits", _o_comment235.data()))) {
            int32_t _o_orderkey227_t = tbl_SerializeFromObject_TD_5927_input.getInt32(i, 0);
            tbl_Filter_TD_4206_output.setInt32(r, 0, _o_orderkey227_t);
            int32_t _o_custkey228_t = tbl_SerializeFromObject_TD_5927_input.getInt32(i, 1);
            tbl_Filter_TD_4206_output.setInt32(r, 1, _o_custkey228_t);
            r++;
        }
    }
    tbl_Filter_TD_4206_output.setNumRow(r);
    std::cout << "tbl_Filter_TD_4206_output #Row: " << tbl_Filter_TD_4206_output.getNumRow() << std::endl;
}


void SW_JOIN_LEFTANTI_TD_3476_concatenate(Table &tbl_JOIN_LEFTANTI_TD_3476_output_preprocess, Table &tbl_JOIN_INNER_TD_0561_output) {
    int start_idx = tbl_JOIN_LEFTANTI_TD_3476_output_preprocess.getNumRow();
    int nrow = tbl_JOIN_INNER_TD_0561_output.getNumRow();
    int i = 0;
    for (int r(start_idx); r<start_idx+nrow; ++r) {
        int32_t _c_custkey125 = tbl_JOIN_INNER_TD_0561_output.getInt32(i, 0);
        tbl_JOIN_LEFTANTI_TD_3476_output_preprocess.setInt32(r, 0, _c_custkey125);
        int32_t _o_orderkey227 = tbl_JOIN_INNER_TD_0561_output.getInt32(i, 1);
        tbl_JOIN_LEFTANTI_TD_3476_output_preprocess.setInt32(r, 1, _o_orderkey227);
        i++;
    }
    tbl_JOIN_LEFTANTI_TD_3476_output_preprocess.setNumRow(start_idx + nrow);
    std::cout << "tbl_JOIN_LEFTANTI_TD_3476_output_preprocess #Row: " << tbl_JOIN_LEFTANTI_TD_3476_output_preprocess.getNumRow() << std::endl;
}

void SW_Aggregate_TD_2488_consolidate(Table &tbl_Aggregate_TD_2488_output_preprocess, Table &tbl_Aggregate_TD_2488_output) {
    int nrow = 0;
    int nrow_p = tbl_Aggregate_TD_2488_output_preprocess.getNumRow();
    for (int r(0); r<nrow_p; ++r) {
        int32_t _c_count1635L = tbl_Aggregate_TD_2488_output_preprocess.getInt32(r, 0);
        tbl_Aggregate_TD_2488_output.setInt32(r, 0, _c_count1635L);
    }
    nrow += nrow_p;
    tbl_Aggregate_TD_2488_output.setNumRow(nrow);
    std::cout << "tbl_Aggregate_TD_2488_output #Row: " << tbl_Aggregate_TD_2488_output.getNumRow() << std::endl;
}

void SW_Aggregate_TD_1527_consolidate(Table &tbl_Aggregate_TD_1527_output_preprocess, Table &tbl_Aggregate_TD_1527_output) {
    int nrow = 0;
    int nrow_p = tbl_Aggregate_TD_1527_output_preprocess.getNumRow();
    for (int r(0); r<nrow_p; ++r) {
        int32_t _c_count1635L = tbl_Aggregate_TD_1527_output_preprocess.getInt32(r, 7);
        tbl_Aggregate_TD_1527_output.setInt32(r, 0, _c_count1635L);
        int32_t _custdist1630L = tbl_Aggregate_TD_1527_output_preprocess.getInt32(r, 0);
        tbl_Aggregate_TD_1527_output.setInt32(r, 1, _custdist1630L);
    }
    nrow += nrow_p;
    tbl_Aggregate_TD_1527_output.setNumRow(nrow);
    std::cout << "tbl_Aggregate_TD_1527_output #Row: " << tbl_Aggregate_TD_1527_output.getNumRow() << std::endl;
}

void SW_Sort_TD_0342(Table &tbl_Aggregate_TD_1527_output, Table &tbl_Sort_TD_0342_output) {
    // StringRowIDSubstitution: false StringRowIDBackSubstitution: false
    // Supported operation: Sort
    // Operation: ListBuffer(custdist#1630L DESC NULLS LAST, c_count#1635L DESC NULLS LAST)
    // Input: ListBuffer(c_count#1635L, custdist#1630L)
    // Output: ListBuffer(c_count#1635L, custdist#1630L)
    struct SW_Sort_TD_0342Row {
        int64_t _c_count1635L;
        int64_t _custdist1630L;
    }; 

    struct {
        bool operator()(const SW_Sort_TD_0342Row& a, const SW_Sort_TD_0342Row& b) const { return 
 (a._custdist1630L > b._custdist1630L) || 
 ((a._custdist1630L == b._custdist1630L) && (a._c_count1635L > b._c_count1635L)); 
}
    }SW_Sort_TD_0342_order; 

    int nrow1 = tbl_Aggregate_TD_1527_output.getNumRow();
    std::vector<SW_Sort_TD_0342Row> rows;
    for (int i = 0; i < nrow1; i++) {
        int64_t _c_count1635L = tbl_Aggregate_TD_1527_output.getInt64(i, 0);
        int64_t _custdist1630L = tbl_Aggregate_TD_1527_output.getInt64(i, 1);
        SW_Sort_TD_0342Row t = {_c_count1635L,_custdist1630L};
        rows.push_back(t);
    }
    std::sort(rows.begin(), rows.end(), SW_Sort_TD_0342_order);
    int r = 0;
    for (auto& it : rows) {
        tbl_Sort_TD_0342_output.setInt64(r, 0, it._c_count1635L);
        tbl_Sort_TD_0342_output.setInt64(r, 1, it._custdist1630L);
        if (r < 10) {
            std::cout << it._c_count1635L << " " << it._custdist1630L << " " << std::endl;
        }
        ++r;
    }
    tbl_Sort_TD_0342_output.setNumRow(r);
    std::cout << "tbl_Sort_TD_0342_output #Row: " << tbl_Sort_TD_0342_output.getNumRow() << std::endl;
}

