#include <regex> 
#include <stdint.h> 

void SW_Filter_TD_7659(Table &tbl_SerializeFromObject_TD_8531_input, Table &tbl_Filter_TD_7659_output) {
    // StringRowIDSubstitution: false StringRowIDBackSubstitution: false
    // Supported operation: Filter
    // Operation: ListBuffer(((o_orderdate#231 >= 19930101) AND (o_orderdate#231 < 19940101)))
    // Input: ListBuffer(o_orderkey#227, o_custkey#228, o_orderdate#231)
    // Output: ListBuffer(o_orderkey#227, o_custkey#228)
    int r = 0;
    int nrow1 = tbl_SerializeFromObject_TD_8531_input.getNumRow();
    for (int i = 0; i < nrow1; i++) {
        int32_t _o_orderdate231 = tbl_SerializeFromObject_TD_8531_input.getInt32(i, 2);
        if ((_o_orderdate231 >= 19930101) && (_o_orderdate231 < 19940101)) {
            int32_t _o_orderkey227_t = tbl_SerializeFromObject_TD_8531_input.getInt32(i, 0);
            tbl_Filter_TD_7659_output.setInt32(r, 0, _o_orderkey227_t);
            int32_t _o_custkey228_t = tbl_SerializeFromObject_TD_8531_input.getInt32(i, 1);
            tbl_Filter_TD_7659_output.setInt32(r, 1, _o_custkey228_t);
            r++;
        }
    }
    tbl_Filter_TD_7659_output.setNumRow(r);
    std::cout << "tbl_Filter_TD_7659_output #Row: " << tbl_Filter_TD_7659_output.getNumRow() << std::endl;
}




void SW_Filter_TD_3828(Table &tbl_SerializeFromObject_TD_4773_input, Table &tbl_Filter_TD_3828_output) {
    // StringRowIDSubstitution: false StringRowIDBackSubstitution: false
    // Supported operation: Filter
    // Operation: ListBuffer((isnotnull(r_name#189) AND (r_name#189 = AFRICA)))
    // Input: ListBuffer(r_regionkey#188, r_name#189)
    // Output: ListBuffer(r_regionkey#188)
    int r = 0;
    int nrow1 = tbl_SerializeFromObject_TD_4773_input.getNumRow();
    for (int i = 0; i < nrow1; i++) {
        std::array<char, TPCH_READ_REGION_LEN + 1> _r_name189 = tbl_SerializeFromObject_TD_4773_input.getcharN<char, TPCH_READ_REGION_LEN + 1>(i, 1);
        if ((1) && (std::string(_r_name189.data()) == "AFRICA")) {
            int32_t _r_regionkey188_t = tbl_SerializeFromObject_TD_4773_input.getInt32(i, 0);
            tbl_Filter_TD_3828_output.setInt32(r, 0, _r_regionkey188_t);
            r++;
        }
    }
    tbl_Filter_TD_3828_output.setNumRow(r);
    std::cout << "tbl_Filter_TD_3828_output #Row: " << tbl_Filter_TD_3828_output.getNumRow() << std::endl;
}

struct SW_JOIN_INNER_TD_3474_key_leftMajor {
    int32_t _s_nationkey371;
    bool operator==(const SW_JOIN_INNER_TD_3474_key_leftMajor& other) const {
        return ((_s_nationkey371 == other._s_nationkey371));
    }
};
namespace std {
template <>
struct hash<SW_JOIN_INNER_TD_3474_key_leftMajor> {
    std::size_t operator() (const SW_JOIN_INNER_TD_3474_key_leftMajor& k) const {
        using std::size_t;
        using std::hash;
        using std::string;
        return (hash<int32_t>()(k._s_nationkey371));
    }
};
}
struct SW_JOIN_INNER_TD_3474_payload_leftMajor {
    int32_t _l_extendedprice55;
    int32_t _l_discount56;
    int32_t _s_nationkey371;
};
struct SW_JOIN_INNER_TD_3474_key_rightMajor {
    int32_t _n_nationkey164;
    bool operator==(const SW_JOIN_INNER_TD_3474_key_rightMajor& other) const {
        return ((_n_nationkey164 == other._n_nationkey164));
    }
};
namespace std {
template <>
struct hash<SW_JOIN_INNER_TD_3474_key_rightMajor> {
    std::size_t operator() (const SW_JOIN_INNER_TD_3474_key_rightMajor& k) const {
        using std::size_t;
        using std::hash;
        using std::string;
        return (hash<int32_t>()(k._n_nationkey164));
    }
};
}
struct SW_JOIN_INNER_TD_3474_payload_rightMajor {
    int32_t _n_nationkey164;
    std::string _n_name165;
    int32_t _n_regionkey166;
};
void SW_JOIN_INNER_TD_3474(Table &tbl_JOIN_INNER_TD_451_output, Table &tbl_SerializeFromObject_TD_4481_input, Table &tbl_JOIN_INNER_TD_3474_output) {
    // StringRowIDSubstitution: false StringRowIDBackSubstitution: false
    // Supported operation: JOIN_INNER
    // Operation: ListBuffer((s_nationkey#371 = n_nationkey#164))
    // Left Table: ListBuffer(l_extendedprice#55, l_discount#56, s_nationkey#371)
    // Right Table: ListBuffer(n_nationkey#164, n_name#165, n_regionkey#166)
    // Output Table: ListBuffer(l_extendedprice#55, l_discount#56, n_name#165, n_regionkey#166)
    int left_nrow = tbl_JOIN_INNER_TD_451_output.getNumRow();
    int right_nrow = tbl_SerializeFromObject_TD_4481_input.getNumRow();
    if (left_nrow < right_nrow) { 
        std::unordered_multimap<SW_JOIN_INNER_TD_3474_key_leftMajor, SW_JOIN_INNER_TD_3474_payload_leftMajor> ht1;
        int nrow1 = tbl_JOIN_INNER_TD_451_output.getNumRow();
        for (int i = 0; i < nrow1; i++) {
            int32_t _s_nationkey371_k = tbl_JOIN_INNER_TD_451_output.getInt32(i, 2);
            SW_JOIN_INNER_TD_3474_key_leftMajor keyA{_s_nationkey371_k};
            int32_t _l_extendedprice55 = tbl_JOIN_INNER_TD_451_output.getInt32(i, 0);
            int32_t _l_discount56 = tbl_JOIN_INNER_TD_451_output.getInt32(i, 1);
            int32_t _s_nationkey371 = tbl_JOIN_INNER_TD_451_output.getInt32(i, 2);
            SW_JOIN_INNER_TD_3474_payload_leftMajor payloadA{_l_extendedprice55, _l_discount56, _s_nationkey371};
            ht1.insert(std::make_pair(keyA, payloadA));
        }
        int r = 0;
        int nrow2 = tbl_SerializeFromObject_TD_4481_input.getNumRow();
        for (int i = 0; i < nrow2; i++) {
            int32_t _n_nationkey164_k = tbl_SerializeFromObject_TD_4481_input.getInt32(i, 0);
            auto its = ht1.equal_range(SW_JOIN_INNER_TD_3474_key_leftMajor{_n_nationkey164_k});
            auto it = its.first;
            while (it != its.second) {
                int32_t _l_extendedprice55 = (it->second)._l_extendedprice55;
                int32_t _l_discount56 = (it->second)._l_discount56;
                int32_t _s_nationkey371 = (it->second)._s_nationkey371;
                int32_t _n_nationkey164 = tbl_SerializeFromObject_TD_4481_input.getInt32(i, 0);
                std::array<char, TPCH_READ_REGION_LEN + 1> _n_name165_n = tbl_SerializeFromObject_TD_4481_input.getcharN<char, TPCH_READ_REGION_LEN + 1>(i, 1);
                std::string _n_name165 = std::string(_n_name165_n.data());
                int32_t _n_regionkey166 = tbl_SerializeFromObject_TD_4481_input.getInt32(i, 2);
                tbl_JOIN_INNER_TD_3474_output.setInt32(r, 0, _l_extendedprice55);
                tbl_JOIN_INNER_TD_3474_output.setInt32(r, 1, _l_discount56);
                tbl_JOIN_INNER_TD_3474_output.setcharN<char, TPCH_READ_REGION_LEN + 1>(r, 2, _n_name165_n);
                tbl_JOIN_INNER_TD_3474_output.setInt32(r, 3, _n_regionkey166);
                it++;
                r++;
            }
        }
        tbl_JOIN_INNER_TD_3474_output.setNumRow(r);
    } else { 
        std::unordered_multimap<SW_JOIN_INNER_TD_3474_key_rightMajor, SW_JOIN_INNER_TD_3474_payload_rightMajor> ht1;
        int nrow1 = tbl_SerializeFromObject_TD_4481_input.getNumRow();
        for (int i = 0; i < nrow1; i++) {
            int32_t _n_nationkey164_k = tbl_SerializeFromObject_TD_4481_input.getInt32(i, 0);
            SW_JOIN_INNER_TD_3474_key_rightMajor keyA{_n_nationkey164_k};
            int32_t _n_nationkey164 = tbl_SerializeFromObject_TD_4481_input.getInt32(i, 0);
            std::array<char, TPCH_READ_REGION_LEN + 1> _n_name165_n = tbl_SerializeFromObject_TD_4481_input.getcharN<char, TPCH_READ_REGION_LEN + 1>(i, 1);
            std::string _n_name165 = std::string(_n_name165_n.data());
            int32_t _n_regionkey166 = tbl_SerializeFromObject_TD_4481_input.getInt32(i, 2);
            SW_JOIN_INNER_TD_3474_payload_rightMajor payloadA{_n_nationkey164, _n_name165, _n_regionkey166};
            ht1.insert(std::make_pair(keyA, payloadA));
        }
        int r = 0;
        int nrow2 = tbl_JOIN_INNER_TD_451_output.getNumRow();
        for (int i = 0; i < nrow2; i++) {
            int32_t _s_nationkey371_k = tbl_JOIN_INNER_TD_451_output.getInt32(i, 2);
            auto its = ht1.equal_range(SW_JOIN_INNER_TD_3474_key_rightMajor{_s_nationkey371_k});
            auto it = its.first;
            while (it != its.second) {
                int32_t _n_nationkey164 = (it->second)._n_nationkey164;
                std::string _n_name165 = (it->second)._n_name165;
                std::array<char, TPCH_READ_REGION_LEN + 1> _n_name165_n{};
                memcpy(_n_name165_n.data(), (_n_name165).data(), (_n_name165).length());
                int32_t _n_regionkey166 = (it->second)._n_regionkey166;
                int32_t _l_extendedprice55 = tbl_JOIN_INNER_TD_451_output.getInt32(i, 0);
                int32_t _l_discount56 = tbl_JOIN_INNER_TD_451_output.getInt32(i, 1);
                int32_t _s_nationkey371 = tbl_JOIN_INNER_TD_451_output.getInt32(i, 2);
                tbl_JOIN_INNER_TD_3474_output.setcharN<char, TPCH_READ_REGION_LEN + 1>(r, 2, _n_name165_n);
                tbl_JOIN_INNER_TD_3474_output.setInt32(r, 3, _n_regionkey166);
                tbl_JOIN_INNER_TD_3474_output.setInt32(r, 0, _l_extendedprice55);
                tbl_JOIN_INNER_TD_3474_output.setInt32(r, 1, _l_discount56);
                it++;
                r++;
            }
        }
        tbl_JOIN_INNER_TD_3474_output.setNumRow(r);
    } 
    std::cout << "tbl_JOIN_INNER_TD_3474_output #Row: " << tbl_JOIN_INNER_TD_3474_output.getNumRow() << std::endl;
}

struct SW_JOIN_INNER_TD_2962_key_leftMajor {
    int32_t _n_regionkey166;
    bool operator==(const SW_JOIN_INNER_TD_2962_key_leftMajor& other) const {
        return ((_n_regionkey166 == other._n_regionkey166));
    }
};
namespace std {
template <>
struct hash<SW_JOIN_INNER_TD_2962_key_leftMajor> {
    std::size_t operator() (const SW_JOIN_INNER_TD_2962_key_leftMajor& k) const {
        using std::size_t;
        using std::hash;
        using std::string;
        return (hash<int32_t>()(k._n_regionkey166));
    }
};
}
struct SW_JOIN_INNER_TD_2962_payload_leftMajor {
    int32_t _l_extendedprice55;
    int32_t _l_discount56;
    std::string _n_name165;
    int32_t _n_regionkey166;
};
struct SW_JOIN_INNER_TD_2962_key_rightMajor {
    int32_t _r_regionkey188;
    bool operator==(const SW_JOIN_INNER_TD_2962_key_rightMajor& other) const {
        return ((_r_regionkey188 == other._r_regionkey188));
    }
};
namespace std {
template <>
struct hash<SW_JOIN_INNER_TD_2962_key_rightMajor> {
    std::size_t operator() (const SW_JOIN_INNER_TD_2962_key_rightMajor& k) const {
        using std::size_t;
        using std::hash;
        using std::string;
        return (hash<int32_t>()(k._r_regionkey188));
    }
};
}
struct SW_JOIN_INNER_TD_2962_payload_rightMajor {
    int32_t _r_regionkey188;
};
void SW_JOIN_INNER_TD_2962(Table &tbl_JOIN_INNER_TD_3474_output, Table &tbl_Filter_TD_3828_output, Table &tbl_JOIN_INNER_TD_2962_output) {
    // StringRowIDSubstitution: false StringRowIDBackSubstitution: false
    // Supported operation: JOIN_INNER
    // Operation: ListBuffer((n_regionkey#166 = r_regionkey#188))
    // Left Table: ListBuffer(l_extendedprice#55, l_discount#56, n_name#165, n_regionkey#166)
    // Right Table: ListBuffer(r_regionkey#188)
    // Output Table: ListBuffer(l_extendedprice#55, l_discount#56, n_name#165)
    int left_nrow = tbl_JOIN_INNER_TD_3474_output.getNumRow();
    int right_nrow = tbl_Filter_TD_3828_output.getNumRow();
    if (left_nrow < right_nrow) { 
        std::unordered_multimap<SW_JOIN_INNER_TD_2962_key_leftMajor, SW_JOIN_INNER_TD_2962_payload_leftMajor> ht1;
        int nrow1 = tbl_JOIN_INNER_TD_3474_output.getNumRow();
        for (int i = 0; i < nrow1; i++) {
            int32_t _n_regionkey166_k = tbl_JOIN_INNER_TD_3474_output.getInt32(i, 3);
            SW_JOIN_INNER_TD_2962_key_leftMajor keyA{_n_regionkey166_k};
            int32_t _l_extendedprice55 = tbl_JOIN_INNER_TD_3474_output.getInt32(i, 0);
            int32_t _l_discount56 = tbl_JOIN_INNER_TD_3474_output.getInt32(i, 1);
            std::array<char, TPCH_READ_REGION_LEN + 1> _n_name165_n = tbl_JOIN_INNER_TD_3474_output.getcharN<char, TPCH_READ_REGION_LEN + 1>(i, 2);
            std::string _n_name165 = std::string(_n_name165_n.data());
            int32_t _n_regionkey166 = tbl_JOIN_INNER_TD_3474_output.getInt32(i, 3);
            SW_JOIN_INNER_TD_2962_payload_leftMajor payloadA{_l_extendedprice55, _l_discount56, _n_name165, _n_regionkey166};
            ht1.insert(std::make_pair(keyA, payloadA));
        }
        int r = 0;
        int nrow2 = tbl_Filter_TD_3828_output.getNumRow();
        for (int i = 0; i < nrow2; i++) {
            int32_t _r_regionkey188_k = tbl_Filter_TD_3828_output.getInt32(i, 0);
            auto its = ht1.equal_range(SW_JOIN_INNER_TD_2962_key_leftMajor{_r_regionkey188_k});
            auto it = its.first;
            while (it != its.second) {
                int32_t _l_extendedprice55 = (it->second)._l_extendedprice55;
                int32_t _l_discount56 = (it->second)._l_discount56;
                std::string _n_name165 = (it->second)._n_name165;
                std::array<char, TPCH_READ_REGION_LEN + 1> _n_name165_n{};
                memcpy(_n_name165_n.data(), (_n_name165).data(), (_n_name165).length());
                int32_t _n_regionkey166 = (it->second)._n_regionkey166;
                int32_t _r_regionkey188 = tbl_Filter_TD_3828_output.getInt32(i, 0);
                tbl_JOIN_INNER_TD_2962_output.setInt32(r, 0, _l_extendedprice55);
                tbl_JOIN_INNER_TD_2962_output.setInt32(r, 1, _l_discount56);
                tbl_JOIN_INNER_TD_2962_output.setcharN<char, TPCH_READ_REGION_LEN + 1>(r, 2, _n_name165_n);
                it++;
                r++;
            }
        }
        tbl_JOIN_INNER_TD_2962_output.setNumRow(r);
    } else { 
        std::unordered_multimap<SW_JOIN_INNER_TD_2962_key_rightMajor, SW_JOIN_INNER_TD_2962_payload_rightMajor> ht1;
        int nrow1 = tbl_Filter_TD_3828_output.getNumRow();
        for (int i = 0; i < nrow1; i++) {
            int32_t _r_regionkey188_k = tbl_Filter_TD_3828_output.getInt32(i, 0);
            SW_JOIN_INNER_TD_2962_key_rightMajor keyA{_r_regionkey188_k};
            int32_t _r_regionkey188 = tbl_Filter_TD_3828_output.getInt32(i, 0);
            SW_JOIN_INNER_TD_2962_payload_rightMajor payloadA{_r_regionkey188};
            ht1.insert(std::make_pair(keyA, payloadA));
        }
        int r = 0;
        int nrow2 = tbl_JOIN_INNER_TD_3474_output.getNumRow();
        for (int i = 0; i < nrow2; i++) {
            int32_t _n_regionkey166_k = tbl_JOIN_INNER_TD_3474_output.getInt32(i, 3);
            auto its = ht1.equal_range(SW_JOIN_INNER_TD_2962_key_rightMajor{_n_regionkey166_k});
            auto it = its.first;
            while (it != its.second) {
                int32_t _r_regionkey188 = (it->second)._r_regionkey188;
                int32_t _l_extendedprice55 = tbl_JOIN_INNER_TD_3474_output.getInt32(i, 0);
                int32_t _l_discount56 = tbl_JOIN_INNER_TD_3474_output.getInt32(i, 1);
                std::array<char, TPCH_READ_REGION_LEN + 1> _n_name165_n = tbl_JOIN_INNER_TD_3474_output.getcharN<char, TPCH_READ_REGION_LEN + 1>(i, 2);
                std::string _n_name165 = std::string(_n_name165_n.data());
                int32_t _n_regionkey166 = tbl_JOIN_INNER_TD_3474_output.getInt32(i, 3);
                tbl_JOIN_INNER_TD_2962_output.setInt32(r, 0, _l_extendedprice55);
                tbl_JOIN_INNER_TD_2962_output.setInt32(r, 1, _l_discount56);
                tbl_JOIN_INNER_TD_2962_output.setcharN<char, TPCH_READ_REGION_LEN + 1>(r, 2, _n_name165_n);
                it++;
                r++;
            }
        }
        tbl_JOIN_INNER_TD_2962_output.setNumRow(r);
    } 
    std::cout << "tbl_JOIN_INNER_TD_2962_output #Row: " << tbl_JOIN_INNER_TD_2962_output.getNumRow() << std::endl;
}

typedef std::string SW_Aggregate_TD_1875_key;
struct SW_Aggregate_TD_1875_payload {
    int64_t _revenue1128L_sum_0;
};
void SW_Aggregate_TD_1875(Table &tbl_JOIN_INNER_TD_2962_output, Table &tbl_Aggregate_TD_1875_output) {
    // StringRowIDSubstitution: false StringRowIDBackSubstitution: false
    // Supported operation: Aggregate
    // Operation: ListBuffer(n_name#165, sum((l_extendedprice#55 * (100 - l_discount#56))) AS revenue#1128L)
    // Input: ListBuffer(l_extendedprice#55, l_discount#56, n_name#165)
    // Output: ListBuffer(n_name#165, revenue#1128L)
    std::unordered_map<SW_Aggregate_TD_1875_key, SW_Aggregate_TD_1875_payload> ht1;
    int nrow1 = tbl_JOIN_INNER_TD_2962_output.getNumRow();
    for (int i = 0; i < nrow1; i++) {
        int32_t _l_extendedprice55 = tbl_JOIN_INNER_TD_2962_output.getInt32(i, 0);
        int32_t _l_discount56 = tbl_JOIN_INNER_TD_2962_output.getInt32(i, 1);
        std::array<char, TPCH_READ_REGION_LEN + 1> _n_name165 = tbl_JOIN_INNER_TD_2962_output.getcharN<char, TPCH_READ_REGION_LEN + 1>(i, 2);
        SW_Aggregate_TD_1875_key k = std::string(_n_name165.data());
        int64_t _revenue1128L_sum_0 = (_l_extendedprice55 * (100 - _l_discount56));
        SW_Aggregate_TD_1875_payload p{_revenue1128L_sum_0};
        auto it = ht1.find(k);
        if (it != ht1.end()) {
            int64_t sum_0 = (it->second)._revenue1128L_sum_0 + _revenue1128L_sum_0;
            p._revenue1128L_sum_0 = sum_0;
            ht1[k] = p;
        } else { 
            ht1.insert(std::make_pair(k, p));
        }
    }
    int r = 0;
    for (auto& it : ht1) {
        std::array<char, TPCH_READ_REGION_LEN + 1> _n_name165{};
        memcpy(_n_name165.data(), (it.first).data(), (it.first).length());
        tbl_Aggregate_TD_1875_output.setcharN<char, TPCH_READ_REGION_LEN + 1>(r, 0, _n_name165);
        int64_t _revenue1128L = (it.second)._revenue1128L_sum_0;
        tbl_Aggregate_TD_1875_output.setInt64(r, 1, _revenue1128L);
        ++r;
    }
    tbl_Aggregate_TD_1875_output.setNumRow(r);
    std::cout << "tbl_Aggregate_TD_1875_output #Row: " << tbl_Aggregate_TD_1875_output.getNumRow() << std::endl;
}

void SW_Sort_TD_0669(Table &tbl_Aggregate_TD_1875_output, Table &tbl_Sort_TD_0669_output) {
    // StringRowIDSubstitution: false StringRowIDBackSubstitution: false
    // Supported operation: Sort
    // Operation: ListBuffer(revenue#1128L DESC NULLS LAST)
    // Input: ListBuffer(n_name#165, revenue#1128L)
    // Output: ListBuffer(n_name#165, revenue#1128L)
    struct SW_Sort_TD_0669Row {
        std::string _n_name165;
        int64_t _revenue1128L;
    }; 

    struct {
        bool operator()(const SW_Sort_TD_0669Row& a, const SW_Sort_TD_0669Row& b) const { return 
 (a._revenue1128L > b._revenue1128L); 
}
    }SW_Sort_TD_0669_order; 

    int nrow1 = tbl_Aggregate_TD_1875_output.getNumRow();
    std::vector<SW_Sort_TD_0669Row> rows;
    for (int i = 0; i < nrow1; i++) {
        std::array<char, TPCH_READ_REGION_LEN + 1> _n_name165 = tbl_Aggregate_TD_1875_output.getcharN<char, TPCH_READ_REGION_LEN +1>(i, 0);
        int64_t _revenue1128L = tbl_Aggregate_TD_1875_output.getInt64(i, 1);
        SW_Sort_TD_0669Row t = {std::string(_n_name165.data()),_revenue1128L};
        rows.push_back(t);
    }
    std::sort(rows.begin(), rows.end(), SW_Sort_TD_0669_order);
    int r = 0;
    for (auto& it : rows) {
        std::array<char, TPCH_READ_REGION_LEN + 1> _n_name165{};
        memcpy(_n_name165.data(), (it._n_name165).data(), (it._n_name165).length());
        tbl_Sort_TD_0669_output.setcharN<char, TPCH_READ_REGION_LEN +1>(r, 0, _n_name165);
        tbl_Sort_TD_0669_output.setInt64(r, 1, it._revenue1128L);
        if (r < 10) {
            std::cout << (it._n_name165).data() << " " << it._revenue1128L << " " << std::endl;
        }
        ++r;
    }
    tbl_Sort_TD_0669_output.setNumRow(r);
    std::cout << "tbl_Sort_TD_0669_output #Row: " << tbl_Sort_TD_0669_output.getNumRow() << std::endl;
}

