#include <regex> 
#include <stdint.h> 

void SW_Filter_TD_8392(Table &tbl_SerializeFromObject_TD_918_input, Table &tbl_Filter_TD_8392_output) {
    // StringRowIDSubstitution: false StringRowIDBackSubstitution: false
    // Supported operation: Filter
    // Operation: ListBuffer((l_receiptdate#62 > l_commitdate#61))
    // Input: ListBuffer(l_orderkey#50, l_suppkey#52, l_receiptdate#62, l_commitdate#61)
    // Output: ListBuffer(l_orderkey#50, l_suppkey#52)
    int r = 0;
    int nrow1 = tbl_SerializeFromObject_TD_918_input.getNumRow();
    for (int i = 0; i < nrow1; i++) {
        int32_t _l_receiptdate62 = tbl_SerializeFromObject_TD_918_input.getInt32(i, 2);
        int32_t _l_commitdate61 = tbl_SerializeFromObject_TD_918_input.getInt32(i, 3);
        if (_l_receiptdate62 > _l_commitdate61) {
            int32_t _l_orderkey50_t = tbl_SerializeFromObject_TD_918_input.getInt32(i, 0);
            tbl_Filter_TD_8392_output.setInt32(r, 0, _l_orderkey50_t);
            int32_t _l_suppkey52_t = tbl_SerializeFromObject_TD_918_input.getInt32(i, 1);
            tbl_Filter_TD_8392_output.setInt32(r, 1, _l_suppkey52_t);
            r++;
        }
    }
    tbl_Filter_TD_8392_output.setNumRow(r);
    std::cout << "tbl_Filter_TD_8392_output #Row: " << tbl_Filter_TD_8392_output.getNumRow() << std::endl;
}

void SW_Filter_TD_7610(Table &tbl_SerializeFromObject_TD_918_input, Table &tbl_Filter_TD_7610_output) {
    // StringRowIDSubstitution: false StringRowIDBackSubstitution: false
    // Supported operation: Filter
    // Operation: ListBuffer((l_receiptdate#62 > l_commitdate#61))
    // Input: ListBuffer(l_orderkey#50, l_suppkey#52, l_receiptdate#62, l_commitdate#61)
    // Output: ListBuffer(l_orderkey#50#2259, l_suppkey#52#2261)
    int r = 0;
    int nrow1 = tbl_SerializeFromObject_TD_918_input.getNumRow();
    for (int i = 0; i < nrow1; i++) {
        int32_t _l_receiptdate62 = tbl_SerializeFromObject_TD_918_input.getInt32(i, 2);
        int32_t _l_commitdate61 = tbl_SerializeFromObject_TD_918_input.getInt32(i, 3);
        if (_l_receiptdate62 > _l_commitdate61) {
            int32_t _l_orderkey502259_t = tbl_SerializeFromObject_TD_918_input.getInt32(i, 0);
            tbl_Filter_TD_7610_output.setInt32(r, 0, _l_orderkey502259_t);
            int32_t _l_suppkey522261_t = tbl_SerializeFromObject_TD_918_input.getInt32(i, 1);
            tbl_Filter_TD_7610_output.setInt32(r, 1, _l_suppkey522261_t);
            r++;
        }
    }
    tbl_Filter_TD_7610_output.setNumRow(r);
    std::cout << "tbl_Filter_TD_7610_output #Row: " << tbl_Filter_TD_7610_output.getNumRow() << std::endl;
}




void SW_Filter_TD_3426(Table &tbl_SerializeFromObject_TD_4156_input, Table &tbl_Filter_TD_3426_output) {
    // StringRowIDSubstitution: true StringRowIDBackSubstitution: false
    // Supported operation: Filter
    // Operation: ListBuffer((isnotnull(n_name#165) AND (n_name#165 = JAPAN)))
    // Input: ListBuffer(n_nationkey#164, n_name#165)
    // Output: ListBuffer(n_nationkey#164)
    int r = 0;
    int nrow1 = tbl_SerializeFromObject_TD_4156_input.getNumRow();
    for (int i = 0; i < nrow1; i++) {
        std::array<char, TPCH_READ_REGION_LEN + 1> _n_name165 = tbl_SerializeFromObject_TD_4156_input.getcharN<char, TPCH_READ_REGION_LEN + 1>(i, 1);
        if ((1) && (std::string(_n_name165.data()) == "JAPAN")) {
            int32_t _n_nationkey164_t = tbl_SerializeFromObject_TD_4156_input.getInt32(i, 0);
            tbl_Filter_TD_3426_output.setInt32(r, 0, _n_nationkey164_t);
            r++;
        }
    }
    tbl_Filter_TD_3426_output.setNumRow(r);
    std::cout << "tbl_Filter_TD_3426_output #Row: " << tbl_Filter_TD_3426_output.getNumRow() << std::endl;
}


void SW_Filter_TD_3910(Table &tbl_SerializeFromObject_TD_5838_input, Table &tbl_Filter_TD_3910_output) {
    // StringRowIDSubstitution: true StringRowIDBackSubstitution: false
    // Supported operation: Filter
    // Operation: ListBuffer((o_orderstatus#229 = 70))
    // Input: ListBuffer(o_orderkey#227, o_orderstatus#229)
    // Output: ListBuffer(o_orderkey#227)
    int r = 0;
    int nrow1 = tbl_SerializeFromObject_TD_5838_input.getNumRow();
    for (int i = 0; i < nrow1; i++) {
        int32_t _o_orderstatus229 = tbl_SerializeFromObject_TD_5838_input.getInt32(i, 1);
        if (_o_orderstatus229 == 70) {
            int32_t _o_orderkey227_t = tbl_SerializeFromObject_TD_5838_input.getInt32(i, 0);
            tbl_Filter_TD_3910_output.setInt32(r, 0, _o_orderkey227_t);
            r++;
        }
    }
    tbl_Filter_TD_3910_output.setNumRow(r);
    std::cout << "tbl_Filter_TD_3910_output #Row: " << tbl_Filter_TD_3910_output.getNumRow() << std::endl;
}



typedef std::string SW_Aggregate_TD_1459_key;
struct SW_Aggregate_TD_1459_payload {
    int64_t _numwait2128L_count_0;
};
void SW_Aggregate_TD_1459(Table &tbl_JOIN_INNER_TD_2744_output, Table &tbl_SerializeFromObject_TD_5343_input, Table &tbl_SerializeFromObject_TD_4156_input, Table &tbl_SerializeFromObject_TD_5838_input, Table &tbl_Aggregate_TD_1459_output) {
    // StringRowIDSubstitution: false StringRowIDBackSubstitution: true
    // Supported operation: Aggregate
    // Operation: ListBuffer(s_name#369, count(1) AS numwait#2128L)
    // Input: ListBuffer(s_name#369)
    // Output: ListBuffer(s_name#369, numwait#2128L)
    std::unordered_map<SW_Aggregate_TD_1459_key, SW_Aggregate_TD_1459_payload> ht1;
    int nrow1 = tbl_JOIN_INNER_TD_2744_output.getNumRow();
    for (int i = 0; i < nrow1; i++) {
        std::array<char, TPCH_READ_REGION_LEN + 1> _s_name369 = tbl_SerializeFromObject_TD_5343_input.getcharN<char, TPCH_READ_REGION_LEN + 1>(tbl_JOIN_INNER_TD_2744_output.getInt32(i, 0), 1);
        SW_Aggregate_TD_1459_key k = std::string(_s_name369.data());
        int64_t _numwait2128L_count_0 = 1 != 0 ? 1 : 0;
        SW_Aggregate_TD_1459_payload p{_numwait2128L_count_0};
        auto it = ht1.find(k);
        if (it != ht1.end()) {
            int64_t count_0 = (it->second)._numwait2128L_count_0 + _numwait2128L_count_0;
            p._numwait2128L_count_0 = count_0;
            ht1[k] = p;
        } else { 
            ht1.insert(std::make_pair(k, p));
        }
    }
    int r = 0;
    for (auto& it : ht1) {
        std::array<char, TPCH_READ_REGION_LEN + 1> _s_name369{};
        memcpy(_s_name369.data(), (it.first).data(), (it.first).length());
        tbl_Aggregate_TD_1459_output.setcharN<char, TPCH_READ_REGION_LEN + 1>(r, 0, _s_name369);
        int64_t _numwait2128L = (it.second)._numwait2128L_count_0;
        tbl_Aggregate_TD_1459_output.setInt64(r, 1, _numwait2128L);
        ++r;
    }
    tbl_Aggregate_TD_1459_output.setNumRow(r);
    std::cout << "tbl_Aggregate_TD_1459_output #Row: " << tbl_Aggregate_TD_1459_output.getNumRow() << std::endl;
}

void SW_Sort_TD_0339(Table &tbl_Aggregate_TD_1459_output, Table &tbl_Sort_TD_0339_output) {
    // StringRowIDSubstitution: false StringRowIDBackSubstitution: false
    // Supported operation: Sort
    // Operation: ListBuffer(numwait#2128L DESC NULLS LAST, s_name#369 ASC NULLS FIRST)
    // Input: ListBuffer(s_name#369, numwait#2128L)
    // Output: ListBuffer(s_name#369, numwait#2128L)
    struct SW_Sort_TD_0339Row {
        std::string _s_name369;
        int64_t _numwait2128L;
    }; 

    struct {
        bool operator()(const SW_Sort_TD_0339Row& a, const SW_Sort_TD_0339Row& b) const { return 
 (a._numwait2128L > b._numwait2128L) || 
 ((a._numwait2128L == b._numwait2128L) && (a._s_name369 < b._s_name369)); 
}
    }SW_Sort_TD_0339_order; 

    int nrow1 = tbl_Aggregate_TD_1459_output.getNumRow();
    std::vector<SW_Sort_TD_0339Row> rows;
    for (int i = 0; i < nrow1; i++) {
        std::array<char, TPCH_READ_REGION_LEN + 1> _s_name369 = tbl_Aggregate_TD_1459_output.getcharN<char, TPCH_READ_REGION_LEN +1>(i, 0);
        int64_t _numwait2128L = tbl_Aggregate_TD_1459_output.getInt64(i, 1);
        SW_Sort_TD_0339Row t = {std::string(_s_name369.data()),_numwait2128L};
        rows.push_back(t);
    }
    std::sort(rows.begin(), rows.end(), SW_Sort_TD_0339_order);
    int r = 0;
    for (auto& it : rows) {
        std::array<char, TPCH_READ_REGION_LEN + 1> _s_name369{};
        memcpy(_s_name369.data(), (it._s_name369).data(), (it._s_name369).length());
        tbl_Sort_TD_0339_output.setcharN<char, TPCH_READ_REGION_LEN +1>(r, 0, _s_name369);
        tbl_Sort_TD_0339_output.setInt64(r, 1, it._numwait2128L);
        if (r < 10) {
            std::cout << (it._s_name369).data() << " " << it._numwait2128L << " " << std::endl;
        }
        ++r;
    }
    tbl_Sort_TD_0339_output.setNumRow(r);
    std::cout << "tbl_Sort_TD_0339_output #Row: " << tbl_Sort_TD_0339_output.getNumRow() << std::endl;
}

