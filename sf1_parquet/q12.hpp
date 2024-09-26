#include <regex> 
#include <stdint.h> 

void SW_Filter_TD_3363(Table &tbl_SerializeFromObject_TD_4161_input, Table &tbl_Filter_TD_3363_output) {
    // StringRowIDSubstitution: true StringRowIDBackSubstitution: false
    // Supported operation: Filter
    // Operation: ListBuffer(((((l_shipmode#64 IN (TRUCK,MAIL) AND (l_commitdate#61 < l_receiptdate#62)) AND (l_shipdate#60 < l_commitdate#61)) AND (l_receiptdate#62 >= 19970101)) AND (l_receiptdate#62 < 19980101)))
    // Input: ListBuffer(l_orderkey#50, l_shipmode#64, l_commitdate#61, l_receiptdate#62, l_shipdate#60)
    // Output: ListBuffer(l_orderkey#50, l_shipmode#64)
    int r = 0;
    int nrow1 = tbl_SerializeFromObject_TD_4161_input.getNumRow();
    for (int i = 0; i < nrow1; i++) {
        std::array<char, TPCH_READ_REGION_LEN + 1> _l_shipmode64 = tbl_SerializeFromObject_TD_4161_input.getcharN<char, TPCH_READ_REGION_LEN + 1>(i, 1);
        int32_t _l_commitdate61 = tbl_SerializeFromObject_TD_4161_input.getInt32(i, 2);
        int32_t _l_receiptdate62 = tbl_SerializeFromObject_TD_4161_input.getInt32(i, 3);
        int32_t _l_shipdate60 = tbl_SerializeFromObject_TD_4161_input.getInt32(i, 4);
        auto reuse_col_str_428 = std::string(_l_shipmode64.data());
        if ((((((reuse_col_str_428 == "TRUCK") || (reuse_col_str_428 == "MAIL") || (0)) && (_l_commitdate61 < _l_receiptdate62)) && (_l_shipdate60 < _l_commitdate61)) && (_l_receiptdate62 >= 19970101)) && (_l_receiptdate62 < 19980101)) {
            int32_t _l_orderkey50_t = tbl_SerializeFromObject_TD_4161_input.getInt32(i, 0);
            tbl_Filter_TD_3363_output.setInt32(r, 0, _l_orderkey50_t);
            tbl_Filter_TD_3363_output.setInt32(r, 1, i);
            r++;
        }
    }
    tbl_Filter_TD_3363_output.setNumRow(r);
    std::cout << "tbl_Filter_TD_3363_output #Row: " << tbl_Filter_TD_3363_output.getNumRow() << std::endl;
}


typedef std::string SW_Aggregate_TD_1238_key;
struct SW_Aggregate_TD_1238_payload {
    int64_t _high_line_count1553L_sum_0;
    int64_t _low_line_count1554L_sum_1;
};
void SW_Aggregate_TD_1238(Table &tbl_JOIN_INNER_TD_2542_output, Table &tbl_SerializeFromObject_TD_3342_input, Table &tbl_SerializeFromObject_TD_4161_input, Table &tbl_Aggregate_TD_1238_output) {
    // StringRowIDSubstitution: false StringRowIDBackSubstitution: true
    // Supported operation: Aggregate
    // Operation: ListBuffer(l_shipmode#64, sum(CASE WHEN ((o_orderpriority#232 = 1-URGENT) OR (o_orderpriority#232 = 2-HIGH)) THEN 1 ELSE 0 END) AS high_line_count#1553L, sum(CASE WHEN (NOT (o_orderpriority#232 = 1-URGENT) AND NOT (o_orderpriority#232 = 2-HIGH)) THEN 1 ELSE 0 END) AS low_line_count#1554L)
    // Input: ListBuffer(o_orderpriority#232, l_shipmode#64)
    // Output: ListBuffer(l_shipmode#64, high_line_count#1553L, low_line_count#1554L)
    std::unordered_map<SW_Aggregate_TD_1238_key, SW_Aggregate_TD_1238_payload> ht1;
    int nrow1 = tbl_JOIN_INNER_TD_2542_output.getNumRow();
    for (int i = 0; i < nrow1; i++) {
        std::array<char, TPCH_READ_REGION_LEN + 1> _o_orderpriority232 = tbl_SerializeFromObject_TD_3342_input.getcharN<char, TPCH_READ_REGION_LEN + 1>(tbl_JOIN_INNER_TD_2542_output.getInt32(i, 0), 1);
        std::array<char, TPCH_READ_REGION_LEN + 1> _l_shipmode64 = tbl_SerializeFromObject_TD_4161_input.getcharN<char, TPCH_READ_REGION_LEN + 1>(tbl_JOIN_INNER_TD_2542_output.getInt32(i, 1), 1);
        SW_Aggregate_TD_1238_key k = std::string(_l_shipmode64.data());
        int64_t _high_line_count1553L_sum_0 = ((std::string(_o_orderpriority232.data()) == "1-URGENT") || (std::string(_o_orderpriority232.data()) == "2-HIGH")) ? 1 : 0;
        int64_t _low_line_count1554L_sum_1 = (!((std::string(_o_orderpriority232.data()) == "1-URGENT")) && !((std::string(_o_orderpriority232.data()) == "2-HIGH"))) ? 1 : 0;
        SW_Aggregate_TD_1238_payload p{_high_line_count1553L_sum_0, _low_line_count1554L_sum_1};
        auto it = ht1.find(k);
        if (it != ht1.end()) {
            int64_t sum_0 = (it->second)._high_line_count1553L_sum_0 + _high_line_count1553L_sum_0;
            p._high_line_count1553L_sum_0 = sum_0;
            int64_t sum_1 = (it->second)._low_line_count1554L_sum_1 + _low_line_count1554L_sum_1;
            p._low_line_count1554L_sum_1 = sum_1;
            ht1[k] = p;
        } else { 
            ht1.insert(std::make_pair(k, p));
        }
    }
    int r = 0;
    for (auto& it : ht1) {
        std::array<char, TPCH_READ_REGION_LEN + 1> _l_shipmode64{};
        memcpy(_l_shipmode64.data(), (it.first).data(), (it.first).length());
        tbl_Aggregate_TD_1238_output.setcharN<char, TPCH_READ_REGION_LEN + 1>(r, 0, _l_shipmode64);
        int64_t _high_line_count1553L = (it.second)._high_line_count1553L_sum_0;
        tbl_Aggregate_TD_1238_output.setInt64(r, 1, _high_line_count1553L);
        int64_t _low_line_count1554L = (it.second)._low_line_count1554L_sum_1;
        tbl_Aggregate_TD_1238_output.setInt64(r, 2, _low_line_count1554L);
        ++r;
    }
    tbl_Aggregate_TD_1238_output.setNumRow(r);
    std::cout << "tbl_Aggregate_TD_1238_output #Row: " << tbl_Aggregate_TD_1238_output.getNumRow() << std::endl;
}

void SW_Sort_TD_0403(Table &tbl_Aggregate_TD_1238_output, Table &tbl_Sort_TD_0403_output) {
    // StringRowIDSubstitution: false StringRowIDBackSubstitution: false
    // Supported operation: Sort
    // Operation: ListBuffer(l_shipmode#64 ASC NULLS FIRST)
    // Input: ListBuffer(l_shipmode#64, high_line_count#1553L, low_line_count#1554L)
    // Output: ListBuffer(l_shipmode#64, high_line_count#1553L, low_line_count#1554L)
    struct SW_Sort_TD_0403Row {
        std::string _l_shipmode64;
        int64_t _high_line_count1553L;
        int64_t _low_line_count1554L;
    }; 

    struct {
        bool operator()(const SW_Sort_TD_0403Row& a, const SW_Sort_TD_0403Row& b) const { return 
 (a._l_shipmode64 < b._l_shipmode64); 
}
    }SW_Sort_TD_0403_order; 

    int nrow1 = tbl_Aggregate_TD_1238_output.getNumRow();
    std::vector<SW_Sort_TD_0403Row> rows;
    for (int i = 0; i < nrow1; i++) {
        std::array<char, TPCH_READ_REGION_LEN + 1> _l_shipmode64 = tbl_Aggregate_TD_1238_output.getcharN<char, TPCH_READ_REGION_LEN +1>(i, 0);
        int64_t _high_line_count1553L = tbl_Aggregate_TD_1238_output.getInt64(i, 1);
        int64_t _low_line_count1554L = tbl_Aggregate_TD_1238_output.getInt64(i, 2);
        SW_Sort_TD_0403Row t = {std::string(_l_shipmode64.data()),_high_line_count1553L,_low_line_count1554L};
        rows.push_back(t);
    }
    std::sort(rows.begin(), rows.end(), SW_Sort_TD_0403_order);
    int r = 0;
    for (auto& it : rows) {
        std::array<char, TPCH_READ_REGION_LEN + 1> _l_shipmode64{};
        memcpy(_l_shipmode64.data(), (it._l_shipmode64).data(), (it._l_shipmode64).length());
        tbl_Sort_TD_0403_output.setcharN<char, TPCH_READ_REGION_LEN +1>(r, 0, _l_shipmode64);
        tbl_Sort_TD_0403_output.setInt64(r, 1, it._high_line_count1553L);
        tbl_Sort_TD_0403_output.setInt64(r, 2, it._low_line_count1554L);
        if (r < 10) {
            std::cout << (it._l_shipmode64).data() << " " << it._high_line_count1553L << " " << it._low_line_count1554L << " " << std::endl;
        }
        ++r;
    }
    tbl_Sort_TD_0403_output.setNumRow(r);
    std::cout << "tbl_Sort_TD_0403_output #Row: " << tbl_Sort_TD_0403_output.getNumRow() << std::endl;
}

