#include <regex> 
#include <stdint.h> 

void SW_Filter_TD_6694(Table &tbl_SerializeFromObject_TD_72_input, Table &tbl_Filter_TD_6694_output) {
    // StringRowIDSubstitution: false StringRowIDBackSubstitution: false
    // Supported operation: Filter
    // Operation: ListBuffer(((l_shipdate#60 >= 19960101) AND (l_shipdate#60 < 19960401)))
    // Input: ListBuffer(l_suppkey#52, l_extendedprice#55, l_discount#56, l_shipdate#60)
    // Output: ListBuffer(l_suppkey#52, l_extendedprice#55, l_discount#56)
    int r = 0;
    int nrow1 = tbl_SerializeFromObject_TD_72_input.getNumRow();
    for (int i = 0; i < nrow1; i++) {
        int32_t _l_shipdate60 = tbl_SerializeFromObject_TD_72_input.getInt32(i, 3);
        if ((_l_shipdate60 >= 19960101) && (_l_shipdate60 < 19960401)) {
            int32_t _l_suppkey52_t = tbl_SerializeFromObject_TD_72_input.getInt32(i, 0);
            tbl_Filter_TD_6694_output.setInt32(r, 0, _l_suppkey52_t);
            int32_t _l_extendedprice55_t = tbl_SerializeFromObject_TD_72_input.getInt32(i, 1);
            tbl_Filter_TD_6694_output.setInt32(r, 1, _l_extendedprice55_t);
            int32_t _l_discount56_t = tbl_SerializeFromObject_TD_72_input.getInt32(i, 2);
            tbl_Filter_TD_6694_output.setInt32(r, 2, _l_discount56_t);
            r++;
        }
    }
    tbl_Filter_TD_6694_output.setNumRow(r);
    std::cout << "tbl_Filter_TD_6694_output #Row: " << tbl_Filter_TD_6694_output.getNumRow() << std::endl;
}

void SW_Aggregate_TD_5179_consolidate(Table &tbl_Aggregate_TD_5179_output_preprocess, Table &tbl_Aggregate_TD_5179_output) {
    int nrow = 0;
    int nrow_p = tbl_Aggregate_TD_5179_output_preprocess.getNumRow();
    for (int r(0); r<nrow_p; ++r) {
        int64_t _total_revenue1713L = tbl_Aggregate_TD_5179_output_preprocess.combineInt64(r, 8, 0);
        tbl_Aggregate_TD_5179_output.setInt64(r, 0, _total_revenue1713L);
    }
    nrow += nrow_p;
    tbl_Aggregate_TD_5179_output.setNumRow(nrow);
    std::cout << "tbl_Aggregate_TD_5179_output #Row: " << tbl_Aggregate_TD_5179_output.getNumRow() << std::endl;
}

void SW_Aggregate_TD_4337(Table &tbl_Aggregate_TD_5179_output, Table &tbl_Aggregate_TD_4337_output) {
    // StringRowIDSubstitution: false StringRowIDBackSubstitution: false
    // Supported operation: Aggregate
    // Operation: ListBuffer(max(total_revenue#1713L) AS max(total_revenue)#1715L)
    // Input: ListBuffer(total_revenue#1713L)
    // Output: ListBuffer(max(total_revenue)#1715L)
    int64_t max_0 = 0;
    int nrow1 = tbl_Aggregate_TD_5179_output.getNumRow();
    for (int i = 0; i < nrow1; i++) {
        int64_t _total_revenue1713L = tbl_Aggregate_TD_5179_output.getInt64(i, 0);
        int64_t _maxtotal_revenue1715L_max_0 = _total_revenue1713L;
        max_0 = max_0 < _maxtotal_revenue1715L_max_0 ? _maxtotal_revenue1715L_max_0 : max_0;
    }
    int r = 0;
    int64_t _maxtotal_revenue1715L = max_0;
    tbl_Aggregate_TD_4337_output.setInt64(r++, 0, _maxtotal_revenue1715L);
    tbl_Aggregate_TD_4337_output.setNumRow(r);
    std::cout << "tbl_Aggregate_TD_4337_output #Row: " << tbl_Aggregate_TD_4337_output.getNumRow() << std::endl;
}

void SW_Aggregate_TD_4461_consolidate(Table &tbl_Aggregate_TD_4461_output_preprocess, Table &tbl_Aggregate_TD_4461_output) {
    int nrow = 0;
    int nrow_p = tbl_Aggregate_TD_4461_output_preprocess.getNumRow();
    for (int r(0); r<nrow_p; ++r) {
        int32_t _l_suppkey52 = tbl_Aggregate_TD_4461_output_preprocess.getInt32(r, 7);
        tbl_Aggregate_TD_4461_output.setInt32(r, 0, _l_suppkey52);
        int64_t _l_discount1711L = tbl_Aggregate_TD_4461_output_preprocess.combineInt64(r, 8, 0);
        tbl_Aggregate_TD_4461_output.setInt64(r, 1, _l_discount1711L);
    }
    nrow += nrow_p;
    tbl_Aggregate_TD_4461_output.setNumRow(nrow);
    std::cout << "tbl_Aggregate_TD_4461_output #Row: " << tbl_Aggregate_TD_4461_output.getNumRow() << std::endl;
}

void SW_Filter_TD_2251(Table &tbl_Aggregate_TD_4461_output, Table &tbl_Aggregate_TD_4337_output, Table &tbl_Filter_TD_2251_output) {
    // StringRowIDSubstitution: false StringRowIDBackSubstitution: false
    // Supported operation: Filter
    // Operation: ListBuffer((isnotnull(sum((l_extendedprice * (100 - l_discount)))#1711L) AND (sum((l_extendedprice * (100 - l_discount)))#1711L = scalar-subquery#1709 [])))
    // Input: ListBuffer(l_suppkey#52, sum((l_extendedprice * (100 - l_discount)))#1711L)
    // Output: ListBuffer(supplier_no#1712, total_revenue#1713L)
    int r = 0;
    int nrow1 = tbl_Aggregate_TD_4461_output.getNumRow();
    for (int i = 0; i < nrow1; i++) {
        int64_t _l_discount1711L = tbl_Aggregate_TD_4461_output.getInt64(i, 1);
        if ((1) && (_l_discount1711L == tbl_Aggregate_TD_4337_output.getInt64(0, 0))) {
            int32_t _supplier_no1712_t = tbl_Aggregate_TD_4461_output.getInt32(i, 0);
            tbl_Filter_TD_2251_output.setInt32(r, 0, _supplier_no1712_t);
            int64_t _total_revenue1713L_t = tbl_Aggregate_TD_4461_output.getInt64(i, 1);
            tbl_Filter_TD_2251_output.setInt64(r, 1, _total_revenue1713L_t);
            r++;
        }
    }
    tbl_Filter_TD_2251_output.setNumRow(r);
    std::cout << "tbl_Filter_TD_2251_output #Row: " << tbl_Filter_TD_2251_output.getNumRow() << std::endl;
}


void SW_Sort_TD_0662(Table &tbl_JOIN_INNER_TD_1197_output, Table &tbl_SerializeFromObject_TD_2111_input, Table &tbl_Sort_TD_0662_output) {
    // StringRowIDSubstitution: false StringRowIDBackSubstitution: true
    // Supported operation: Sort
    // Operation: ListBuffer(s_suppkey#368 ASC NULLS FIRST)
    // Input: ListBuffer(s_suppkey#368, s_name#369, s_address#370, s_phone#372, total_revenue#1713L)
    // Output: ListBuffer(s_suppkey#368, s_name#369, s_address#370, s_phone#372, total_revenue#1713L)
    struct SW_Sort_TD_0662Row {
        int32_t _s_suppkey368;
        std::string _s_name369;
        std::string _s_address370;
        std::string _s_phone372;
        int64_t _total_revenue1713L;
    }; 

    struct {
        bool operator()(const SW_Sort_TD_0662Row& a, const SW_Sort_TD_0662Row& b) const { return 
 (a._s_suppkey368 < b._s_suppkey368); 
}
    }SW_Sort_TD_0662_order; 

    int nrow1 = tbl_JOIN_INNER_TD_1197_output.getNumRow();
    std::vector<SW_Sort_TD_0662Row> rows;
    for (int i = 0; i < nrow1; i++) {
        int32_t _s_suppkey368 = tbl_JOIN_INNER_TD_1197_output.getInt32(i, 0);
        std::array<char, TPCH_READ_REGION_LEN + 1> _s_name369 = tbl_SerializeFromObject_TD_2111_input.getcharN<char, TPCH_READ_REGION_LEN + 1>(tbl_JOIN_INNER_TD_1197_output.getInt32(i, 1), 3);
        std::array<char, TPCH_READ_REGION_LEN + 1> _s_address370 = tbl_SerializeFromObject_TD_2111_input.getcharN<char, TPCH_READ_REGION_LEN + 1>(tbl_JOIN_INNER_TD_1197_output.getInt32(i, 2), 3);
        std::array<char, TPCH_READ_REGION_LEN + 1> _s_phone372 = tbl_SerializeFromObject_TD_2111_input.getcharN<char, TPCH_READ_REGION_LEN + 1>(tbl_JOIN_INNER_TD_1197_output.getInt32(i, 3), 3);
        int64_t _total_revenue1713L = tbl_JOIN_INNER_TD_1197_output.getInt64(i, 4);
        SW_Sort_TD_0662Row t = {_s_suppkey368,std::string(_s_name369.data()),std::string(_s_address370.data()),std::string(_s_phone372.data()),_total_revenue1713L};
        rows.push_back(t);
    }
    std::sort(rows.begin(), rows.end(), SW_Sort_TD_0662_order);
    int r = 0;
    for (auto& it : rows) {
        tbl_Sort_TD_0662_output.setInt32(r, 0, it._s_suppkey368);
        std::array<char, TPCH_READ_REGION_LEN + 1> _s_name369{};
        memcpy(_s_name369.data(), (it._s_name369).data(), (it._s_name369).length());
        tbl_Sort_TD_0662_output.setcharN<char, TPCH_READ_REGION_LEN +1>(r, 1, _s_name369);
        std::array<char, TPCH_READ_REGION_LEN + 1> _s_address370{};
        memcpy(_s_address370.data(), (it._s_address370).data(), (it._s_address370).length());
        tbl_Sort_TD_0662_output.setcharN<char, TPCH_READ_REGION_LEN +1>(r, 2, _s_address370);
        std::array<char, TPCH_READ_REGION_LEN + 1> _s_phone372{};
        memcpy(_s_phone372.data(), (it._s_phone372).data(), (it._s_phone372).length());
        tbl_Sort_TD_0662_output.setcharN<char, TPCH_READ_REGION_LEN +1>(r, 3, _s_phone372);
        tbl_Sort_TD_0662_output.setInt64(r, 4, it._total_revenue1713L);
        if (r < 10) {
            std::cout << it._s_suppkey368 << " " << (it._s_name369).data() << " " << (it._s_address370).data() << " " << (it._s_phone372).data() << " " << it._total_revenue1713L << " " << std::endl;
        }
        ++r;
    }
    tbl_Sort_TD_0662_output.setNumRow(r);
    std::cout << "tbl_Sort_TD_0662_output #Row: " << tbl_Sort_TD_0662_output.getNumRow() << std::endl;
}

