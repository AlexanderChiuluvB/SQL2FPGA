#include <regex> 
#include <stdint.h> 

void SW_Filter_TD_4451(Table &tbl_SerializeFromObject_TD_5145_input, Table &tbl_Filter_TD_4451_output) {
    // StringRowIDSubstitution: false StringRowIDBackSubstitution: false
    // Supported operation: Filter
    // Operation: ListBuffer(((o_orderdate#231 < 19950307) AND (o_orderdate#231 > 19950214)))
    // Input: ListBuffer(o_orderkey#227, o_custkey#228, o_orderdate#231, o_shippriority#234)
    // Output: ListBuffer(o_orderkey#227, o_custkey#228, o_orderdate#231, o_shippriority#234)
    int r = 0;
    int nrow1 = tbl_SerializeFromObject_TD_5145_input.getNumRow();
    for (int i = 0; i < nrow1; i++) {
        int32_t _o_orderdate231 = tbl_SerializeFromObject_TD_5145_input.getInt32(i, 2);
        if ((_o_orderdate231 < 19950307) && (_o_orderdate231 > 19950214)) {
            int32_t _o_orderkey227_t = tbl_SerializeFromObject_TD_5145_input.getInt32(i, 0);
            tbl_Filter_TD_4451_output.setInt32(r, 0, _o_orderkey227_t);
            int32_t _o_custkey228_t = tbl_SerializeFromObject_TD_5145_input.getInt32(i, 1);
            tbl_Filter_TD_4451_output.setInt32(r, 1, _o_custkey228_t);
            int32_t _o_orderdate231_t = tbl_SerializeFromObject_TD_5145_input.getInt32(i, 2);
            tbl_Filter_TD_4451_output.setInt32(r, 2, _o_orderdate231_t);
            int32_t _o_shippriority234_t = tbl_SerializeFromObject_TD_5145_input.getInt32(i, 3);
            tbl_Filter_TD_4451_output.setInt32(r, 3, _o_shippriority234_t);
            r++;
        }
    }
    tbl_Filter_TD_4451_output.setNumRow(r);
    std::cout << "tbl_Filter_TD_4451_output #Row: " << tbl_Filter_TD_4451_output.getNumRow() << std::endl;
}

void SW_Filter_TD_4390(Table &tbl_SerializeFromObject_TD_5351_input, Table &tbl_Filter_TD_4390_output) {
    // StringRowIDSubstitution: false StringRowIDBackSubstitution: false
    // Supported operation: Filter
    // Operation: ListBuffer((isnotnull(c_mktsegment#131) AND (c_mktsegment#131 = MACHINERY)))
    // Input: ListBuffer(c_custkey#125, c_mktsegment#131)
    // Output: ListBuffer(c_custkey#125)
    int r = 0;
    int nrow1 = tbl_SerializeFromObject_TD_5351_input.getNumRow();
    for (int i = 0; i < nrow1; i++) {
        std::array<char, TPCH_READ_REGION_LEN + 1> _c_mktsegment131 = tbl_SerializeFromObject_TD_5351_input.getcharN<char, TPCH_READ_REGION_LEN + 1>(i, 1);
        if ((1) && (std::string(_c_mktsegment131.data()) == "MACHINERY")) {
            int32_t _c_custkey125_t = tbl_SerializeFromObject_TD_5351_input.getInt32(i, 0);
            tbl_Filter_TD_4390_output.setInt32(r, 0, _c_custkey125_t);
            r++;
        }
    }
    tbl_Filter_TD_4390_output.setNumRow(r);
    std::cout << "tbl_Filter_TD_4390_output #Row: " << tbl_Filter_TD_4390_output.getNumRow() << std::endl;
}

void SW_Filter_TD_3948(Table &tbl_SerializeFromObject_TD_4314_input, Table &tbl_Filter_TD_3948_output) {
    // StringRowIDSubstitution: false StringRowIDBackSubstitution: false
    // Supported operation: Filter
    // Operation: ListBuffer((l_shipdate#60 > 19950307))
    // Input: ListBuffer(l_orderkey#50, l_extendedprice#55, l_discount#56, l_shipdate#60)
    // Output: ListBuffer(l_orderkey#50, l_extendedprice#55, l_discount#56)
    int r = 0;
    int nrow1 = tbl_SerializeFromObject_TD_4314_input.getNumRow();
    for (int i = 0; i < nrow1; i++) {
        int32_t _l_shipdate60 = tbl_SerializeFromObject_TD_4314_input.getInt32(i, 3);
        if (_l_shipdate60 > 19950307) {
            int32_t _l_orderkey50_t = tbl_SerializeFromObject_TD_4314_input.getInt32(i, 0);
            tbl_Filter_TD_3948_output.setInt32(r, 0, _l_orderkey50_t);
            int32_t _l_extendedprice55_t = tbl_SerializeFromObject_TD_4314_input.getInt32(i, 1);
            tbl_Filter_TD_3948_output.setInt32(r, 1, _l_extendedprice55_t);
            int32_t _l_discount56_t = tbl_SerializeFromObject_TD_4314_input.getInt32(i, 2);
            tbl_Filter_TD_3948_output.setInt32(r, 2, _l_discount56_t);
            r++;
        }
    }
    tbl_Filter_TD_3948_output.setNumRow(r);
    std::cout << "tbl_Filter_TD_3948_output #Row: " << tbl_Filter_TD_3948_output.getNumRow() << std::endl;
}



void SW_Aggregate_TD_1746_consolidate(Table &tbl_Aggregate_TD_1746_output_preprocess, Table &tbl_Aggregate_TD_1746_output) {
    int nrow = 0;
    int nrow_p = tbl_Aggregate_TD_1746_output_preprocess.getNumRow();
    for (int r(0); r<nrow_p; ++r) {
        int32_t _l_orderkey50 = tbl_Aggregate_TD_1746_output_preprocess.getInt32(r, 7);
        tbl_Aggregate_TD_1746_output.setInt32(r, 0, _l_orderkey50);
        int64_t _revenue1053L = tbl_Aggregate_TD_1746_output_preprocess.combineInt64(r, 8, 0);
        tbl_Aggregate_TD_1746_output.setInt64(r, 1, _revenue1053L);
        int32_t _o_orderdate231 = tbl_Aggregate_TD_1746_output_preprocess.getInt32(r, 6);
        tbl_Aggregate_TD_1746_output.setInt32(r, 2, _o_orderdate231);
        int32_t _o_shippriority234 = tbl_Aggregate_TD_1746_output_preprocess.getInt32(r, 5);
        tbl_Aggregate_TD_1746_output.setInt32(r, 3, _o_shippriority234);
    }
    nrow += nrow_p;
    tbl_Aggregate_TD_1746_output.setNumRow(nrow);
    std::cout << "tbl_Aggregate_TD_1746_output #Row: " << tbl_Aggregate_TD_1746_output.getNumRow() << std::endl;
}

void SW_Sort_TD_041(Table &tbl_Aggregate_TD_1746_output, Table &tbl_Sort_TD_041_output) {
    // StringRowIDSubstitution: false StringRowIDBackSubstitution: false
    // Supported operation: Sort
    // Operation: ListBuffer(revenue#1053L DESC NULLS LAST, o_orderdate#231 ASC NULLS FIRST)
    // Input: ListBuffer(l_orderkey#50, revenue#1053L, o_orderdate#231, o_shippriority#234)
    // Output: ListBuffer(l_orderkey#50, revenue#1053L, o_orderdate#231, o_shippriority#234)
    struct SW_Sort_TD_041Row {
        int32_t _l_orderkey50;
        int64_t _revenue1053L;
        int32_t _o_orderdate231;
        int32_t _o_shippriority234;
    }; 

    struct {
        bool operator()(const SW_Sort_TD_041Row& a, const SW_Sort_TD_041Row& b) const { return 
 (a._revenue1053L > b._revenue1053L) || 
 ((a._revenue1053L == b._revenue1053L) && (a._o_orderdate231 < b._o_orderdate231)); 
}
    }SW_Sort_TD_041_order; 

    int nrow1 = tbl_Aggregate_TD_1746_output.getNumRow();
    std::vector<SW_Sort_TD_041Row> rows;
    for (int i = 0; i < nrow1; i++) {
        int32_t _l_orderkey50 = tbl_Aggregate_TD_1746_output.getInt32(i, 0);
        int64_t _revenue1053L = tbl_Aggregate_TD_1746_output.getInt64(i, 1);
        int32_t _o_orderdate231 = tbl_Aggregate_TD_1746_output.getInt32(i, 2);
        int32_t _o_shippriority234 = tbl_Aggregate_TD_1746_output.getInt32(i, 3);
        SW_Sort_TD_041Row t = {_l_orderkey50,_revenue1053L,_o_orderdate231,_o_shippriority234};
        rows.push_back(t);
    }
    std::sort(rows.begin(), rows.end(), SW_Sort_TD_041_order);
    int r = 0;
    for (auto& it : rows) {
        tbl_Sort_TD_041_output.setInt32(r, 0, it._l_orderkey50);
        tbl_Sort_TD_041_output.setInt64(r, 1, it._revenue1053L);
        tbl_Sort_TD_041_output.setInt32(r, 2, it._o_orderdate231);
        tbl_Sort_TD_041_output.setInt32(r, 3, it._o_shippriority234);
        if (r < 10) {
            std::cout << it._l_orderkey50 << " " << it._revenue1053L << " " << it._o_orderdate231 << " " << it._o_shippriority234 << " " << std::endl;
        }
        ++r;
    }
    tbl_Sort_TD_041_output.setNumRow(r);
    std::cout << "tbl_Sort_TD_041_output #Row: " << tbl_Sort_TD_041_output.getNumRow() << std::endl;
}

