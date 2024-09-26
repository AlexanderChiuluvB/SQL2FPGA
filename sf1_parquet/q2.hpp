#include <regex> 
#include <stdint.h> 


void SW_Filter_TD_8126(Table &tbl_SerializeFromObject_TD_9370_input, Table &tbl_Filter_TD_8126_output) {
    // StringRowIDSubstitution: false StringRowIDBackSubstitution: false
    // Supported operation: Filter
    // Operation: ListBuffer((isnotnull(r_name#189) AND (r_name#189 = AMERICA)))
    // Input: ListBuffer(r_regionkey#188, r_name#189)
    // Output: ListBuffer(r_regionkey#188)
    int r = 0;
    int nrow1 = tbl_SerializeFromObject_TD_9370_input.getNumRow();
    for (int i = 0; i < nrow1; i++) {
        std::array<char, TPCH_READ_REGION_LEN + 1> _r_name189 = tbl_SerializeFromObject_TD_9370_input.getcharN<char, TPCH_READ_REGION_LEN + 1>(i, 1);
        if ((1) && (std::string(_r_name189.data()) == "AMERICA")) {
            int32_t _r_regionkey188_t = tbl_SerializeFromObject_TD_9370_input.getInt32(i, 0);
            tbl_Filter_TD_8126_output.setInt32(r, 0, _r_regionkey188_t);
            r++;
        }
    }
    tbl_Filter_TD_8126_output.setNumRow(r);
    std::cout << "tbl_Filter_TD_8126_output #Row: " << tbl_Filter_TD_8126_output.getNumRow() << std::endl;
}



void SW_Filter_TD_6426(Table &tbl_SerializeFromObject_TD_7781_input, Table &tbl_Filter_TD_6426_output) {
    // StringRowIDSubstitution: true StringRowIDBackSubstitution: false
    // Supported operation: Filter
    // Operation: ListBuffer((isnotnull(p_type#288) AND ((p_size#289 = 19) AND EndsWith(p_type#288, NICKEL))))
    // Input: ListBuffer(p_partkey#284, p_mfgr#286, p_type#288, p_size#289)
    // Output: ListBuffer(p_partkey#284, p_mfgr#286)
    int r = 0;
    int nrow1 = tbl_SerializeFromObject_TD_7781_input.getNumRow();
    for (int i = 0; i < nrow1; i++) {
        std::array<char, TPCH_READ_REGION_LEN + 1> _p_type288 = tbl_SerializeFromObject_TD_7781_input.getcharN<char, TPCH_READ_REGION_LEN + 1>(i, 2);
        int32_t _p_size289 = tbl_SerializeFromObject_TD_7781_input.getInt32(i, 3);
        if ((1) && ((_p_size289 == 19) && (std::string(_p_type288.data()).find("NICKEL")==std::string(_p_type288.data()).length() - 6))) {
            int32_t _p_partkey284_t = tbl_SerializeFromObject_TD_7781_input.getInt32(i, 0);
            tbl_Filter_TD_6426_output.setInt32(r, 0, _p_partkey284_t);
            tbl_Filter_TD_6426_output.setInt32(r, 1, i);
            r++;
        }
    }
    tbl_Filter_TD_6426_output.setNumRow(r);
    std::cout << "tbl_Filter_TD_6426_output #Row: " << tbl_Filter_TD_6426_output.getNumRow() << std::endl;
}

typedef int32_t SW_Aggregate_TD_6742_key;
struct SW_Aggregate_TD_6742_payload {
    int32_t _minps_supplycost955_min_0;
    int32_t _ps_partkey3291038;
};
void SW_Aggregate_TD_6742(Table &tbl_JOIN_INNER_TD_7289_output, Table &tbl_Aggregate_TD_6742_output) {
    // StringRowIDSubstitution: false StringRowIDBackSubstitution: false
    // Supported operation: Aggregate
    // Operation: ListBuffer(ps_partkey#329, min(ps_supplycost#332) AS min(ps_supplycost)#955, ps_partkey#329 AS ps_partkey#329#1038)
    // Input: ListBuffer(ps_partkey#329, ps_supplycost#332)
    // Output: ListBuffer(min(ps_supplycost)#955, ps_partkey#329#1038)
    std::unordered_map<SW_Aggregate_TD_6742_key, SW_Aggregate_TD_6742_payload> ht1;
    int nrow1 = tbl_JOIN_INNER_TD_7289_output.getNumRow();
    for (int i = 0; i < nrow1; i++) {
        int32_t _ps_partkey329 = tbl_JOIN_INNER_TD_7289_output.getInt32(i, 0);
        int32_t _ps_supplycost332 = tbl_JOIN_INNER_TD_7289_output.getInt32(i, 1);
        SW_Aggregate_TD_6742_key k = _ps_partkey329;
        int32_t _minps_supplycost955_min_0 = _ps_supplycost332;
        int32_t _ps_partkey3291038 = _ps_partkey329;
        SW_Aggregate_TD_6742_payload p{_minps_supplycost955_min_0, _ps_partkey3291038};
        auto it = ht1.find(k);
        if (it != ht1.end()) {
            int32_t min_0 = (it->second)._minps_supplycost955_min_0 > _minps_supplycost955_min_0 ? _minps_supplycost955_min_0 : (it->second)._minps_supplycost955_min_0;
            p._minps_supplycost955_min_0 = min_0;
            ht1[k] = p;
        } else { 
            ht1.insert(std::make_pair(k, p));
        }
    }
    int r = 0;
    for (auto& it : ht1) {
        // _ps_partkey329 not required in the output table
        int32_t _minps_supplycost955 = (it.second)._minps_supplycost955_min_0;
        tbl_Aggregate_TD_6742_output.setInt32(r, 0, _minps_supplycost955);
        tbl_Aggregate_TD_6742_output.setInt32(r, 1, (it.second)._ps_partkey3291038);
        ++r;
    }
    tbl_Aggregate_TD_6742_output.setNumRow(r);
    std::cout << "tbl_Aggregate_TD_6742_output #Row: " << tbl_Aggregate_TD_6742_output.getNumRow() << std::endl;
}


struct SW_JOIN_INNER_TD_4283_key_leftMajor {
    int32_t _ps_supplycost332;
    int32_t _p_partkey284;
    bool operator==(const SW_JOIN_INNER_TD_4283_key_leftMajor& other) const {
        return ((_ps_supplycost332 == other._ps_supplycost332) && (_p_partkey284 == other._p_partkey284));
    }
};
namespace std {
template <>
struct hash<SW_JOIN_INNER_TD_4283_key_leftMajor> {
    std::size_t operator() (const SW_JOIN_INNER_TD_4283_key_leftMajor& k) const {
        using std::size_t;
        using std::hash;
        using std::string;
        return (hash<int32_t>()(k._ps_supplycost332)) + (hash<int32_t>()(k._p_partkey284));
    }
};
}
struct SW_JOIN_INNER_TD_4283_payload_leftMajor {
    int32_t _p_partkey284;
    int32_t _p_mfgr286;
    int32_t _ps_suppkey330;
    int32_t _ps_supplycost332;
};
struct SW_JOIN_INNER_TD_4283_key_rightMajor {
    int32_t _minps_supplycost955;
    int32_t _ps_partkey3291038;
    bool operator==(const SW_JOIN_INNER_TD_4283_key_rightMajor& other) const {
        return ((_minps_supplycost955 == other._minps_supplycost955) && (_ps_partkey3291038 == other._ps_partkey3291038));
    }
};
namespace std {
template <>
struct hash<SW_JOIN_INNER_TD_4283_key_rightMajor> {
    std::size_t operator() (const SW_JOIN_INNER_TD_4283_key_rightMajor& k) const {
        using std::size_t;
        using std::hash;
        using std::string;
        return (hash<int32_t>()(k._minps_supplycost955)) + (hash<int32_t>()(k._ps_partkey3291038));
    }
};
}
struct SW_JOIN_INNER_TD_4283_payload_rightMajor {
    int32_t _minps_supplycost955;
    int32_t _ps_partkey3291038;
};
void SW_JOIN_INNER_TD_4283(Table &tbl_JOIN_INNER_TD_5202_output, Table &tbl_Aggregate_TD_6742_output, Table &tbl_JOIN_INNER_TD_4283_output) {
    // StringRowIDSubstitution: true StringRowIDBackSubstitution: false
    // Supported operation: JOIN_INNER
    // Operation: ListBuffer(((ps_supplycost#332 = min(ps_supplycost)#955) AND (p_partkey#284 = ps_partkey#329#1038)))
    // Left Table: ListBuffer(p_partkey#284, p_mfgr#286, ps_suppkey#330, ps_supplycost#332)
    // Right Table: ListBuffer(min(ps_supplycost)#955, ps_partkey#329#1038)
    // Output Table: ListBuffer(p_partkey#284, p_mfgr#286, ps_suppkey#330)
    int left_nrow = tbl_JOIN_INNER_TD_5202_output.getNumRow();
    int right_nrow = tbl_Aggregate_TD_6742_output.getNumRow();
    if (left_nrow < right_nrow) { 
        std::unordered_multimap<SW_JOIN_INNER_TD_4283_key_leftMajor, SW_JOIN_INNER_TD_4283_payload_leftMajor> ht1;
        int nrow1 = tbl_JOIN_INNER_TD_5202_output.getNumRow();
        for (int i = 0; i < nrow1; i++) {
            int32_t _ps_supplycost332_k = tbl_JOIN_INNER_TD_5202_output.getInt32(i, 3);
            int32_t _p_partkey284_k = tbl_JOIN_INNER_TD_5202_output.getInt32(i, 0);
            SW_JOIN_INNER_TD_4283_key_leftMajor keyA{_ps_supplycost332_k, _p_partkey284_k};
            int32_t _p_partkey284 = tbl_JOIN_INNER_TD_5202_output.getInt32(i, 0);
            int32_t _p_mfgr286 = tbl_JOIN_INNER_TD_5202_output.getInt32(i, 1);
            int32_t _ps_suppkey330 = tbl_JOIN_INNER_TD_5202_output.getInt32(i, 2);
            int32_t _ps_supplycost332 = tbl_JOIN_INNER_TD_5202_output.getInt32(i, 3);
            SW_JOIN_INNER_TD_4283_payload_leftMajor payloadA{_p_partkey284, _p_mfgr286, _ps_suppkey330, _ps_supplycost332};
            ht1.insert(std::make_pair(keyA, payloadA));
        }
        int r = 0;
        int nrow2 = tbl_Aggregate_TD_6742_output.getNumRow();
        for (int i = 0; i < nrow2; i++) {
            int32_t _minps_supplycost955_k = tbl_Aggregate_TD_6742_output.getInt32(i, 0);
            int32_t _ps_partkey3291038_k = tbl_Aggregate_TD_6742_output.getInt32(i, 1);
            auto its = ht1.equal_range(SW_JOIN_INNER_TD_4283_key_leftMajor{_minps_supplycost955_k, _ps_partkey3291038_k});
            auto it = its.first;
            while (it != its.second) {
                int32_t _p_partkey284 = (it->second)._p_partkey284;
                int32_t _p_mfgr286 = (it->second)._p_mfgr286;
                int32_t _ps_suppkey330 = (it->second)._ps_suppkey330;
                int32_t _ps_supplycost332 = (it->second)._ps_supplycost332;
                int32_t _minps_supplycost955 = tbl_Aggregate_TD_6742_output.getInt32(i, 0);
                int32_t _ps_partkey3291038 = tbl_Aggregate_TD_6742_output.getInt32(i, 1);
                tbl_JOIN_INNER_TD_4283_output.setInt32(r, 0, _p_partkey284);
                tbl_JOIN_INNER_TD_4283_output.setInt32(r, 1, _p_mfgr286);
                tbl_JOIN_INNER_TD_4283_output.setInt32(r, 2, _ps_suppkey330);
                it++;
                r++;
            }
        }
        tbl_JOIN_INNER_TD_4283_output.setNumRow(r);
    } else { 
        std::unordered_multimap<SW_JOIN_INNER_TD_4283_key_rightMajor, SW_JOIN_INNER_TD_4283_payload_rightMajor> ht1;
        int nrow1 = tbl_Aggregate_TD_6742_output.getNumRow();
        for (int i = 0; i < nrow1; i++) {
            int32_t _minps_supplycost955_k = tbl_Aggregate_TD_6742_output.getInt32(i, 0);
            int32_t _ps_partkey3291038_k = tbl_Aggregate_TD_6742_output.getInt32(i, 1);
            SW_JOIN_INNER_TD_4283_key_rightMajor keyA{_minps_supplycost955_k, _ps_partkey3291038_k};
            int32_t _minps_supplycost955 = tbl_Aggregate_TD_6742_output.getInt32(i, 0);
            int32_t _ps_partkey3291038 = tbl_Aggregate_TD_6742_output.getInt32(i, 1);
            SW_JOIN_INNER_TD_4283_payload_rightMajor payloadA{_minps_supplycost955, _ps_partkey3291038};
            ht1.insert(std::make_pair(keyA, payloadA));
        }
        int r = 0;
        int nrow2 = tbl_JOIN_INNER_TD_5202_output.getNumRow();
        for (int i = 0; i < nrow2; i++) {
            int32_t _ps_supplycost332_k = tbl_JOIN_INNER_TD_5202_output.getInt32(i, 3);
            int32_t _p_partkey284_k = tbl_JOIN_INNER_TD_5202_output.getInt32(i, 0);
            auto its = ht1.equal_range(SW_JOIN_INNER_TD_4283_key_rightMajor{_ps_supplycost332_k, _p_partkey284_k});
            auto it = its.first;
            while (it != its.second) {
                int32_t _minps_supplycost955 = (it->second)._minps_supplycost955;
                int32_t _ps_partkey3291038 = (it->second)._ps_partkey3291038;
                int32_t _p_partkey284 = tbl_JOIN_INNER_TD_5202_output.getInt32(i, 0);
                int32_t _p_mfgr286 = tbl_JOIN_INNER_TD_5202_output.getInt32(i, 1);
                int32_t _ps_suppkey330 = tbl_JOIN_INNER_TD_5202_output.getInt32(i, 2);
                int32_t _ps_supplycost332 = tbl_JOIN_INNER_TD_5202_output.getInt32(i, 3);
                tbl_JOIN_INNER_TD_4283_output.setInt32(r, 0, _p_partkey284);
                tbl_JOIN_INNER_TD_4283_output.setInt32(r, 1, _p_mfgr286);
                tbl_JOIN_INNER_TD_4283_output.setInt32(r, 2, _ps_suppkey330);
                it++;
                r++;
            }
        }
        tbl_JOIN_INNER_TD_4283_output.setNumRow(r);
    } 
    std::cout << "tbl_JOIN_INNER_TD_4283_output #Row: " << tbl_JOIN_INNER_TD_4283_output.getNumRow() << std::endl;
}

struct SW_JOIN_INNER_TD_394_key_leftMajor {
    int32_t _ps_suppkey330;
    bool operator==(const SW_JOIN_INNER_TD_394_key_leftMajor& other) const {
        return ((_ps_suppkey330 == other._ps_suppkey330));
    }
};
namespace std {
template <>
struct hash<SW_JOIN_INNER_TD_394_key_leftMajor> {
    std::size_t operator() (const SW_JOIN_INNER_TD_394_key_leftMajor& k) const {
        using std::size_t;
        using std::hash;
        using std::string;
        return (hash<int32_t>()(k._ps_suppkey330));
    }
};
}
struct SW_JOIN_INNER_TD_394_payload_leftMajor {
    int32_t _p_partkey284;
    int32_t _p_mfgr286;
    int32_t _ps_suppkey330;
};
struct SW_JOIN_INNER_TD_394_key_rightMajor {
    int32_t _s_suppkey368;
    bool operator==(const SW_JOIN_INNER_TD_394_key_rightMajor& other) const {
        return ((_s_suppkey368 == other._s_suppkey368));
    }
};
namespace std {
template <>
struct hash<SW_JOIN_INNER_TD_394_key_rightMajor> {
    std::size_t operator() (const SW_JOIN_INNER_TD_394_key_rightMajor& k) const {
        using std::size_t;
        using std::hash;
        using std::string;
        return (hash<int32_t>()(k._s_suppkey368));
    }
};
}
struct SW_JOIN_INNER_TD_394_payload_rightMajor {
    int32_t _s_suppkey368;
    int32_t _s_name369;
    int32_t _s_address370;
    int32_t _s_nationkey371;
    int32_t _s_phone372;
    int32_t _s_acctbal373;
    int32_t _s_comment374;
};
void SW_JOIN_INNER_TD_394(Table &tbl_JOIN_INNER_TD_4283_output, Table &tbl_SerializeFromObject_TD_4583_input_stringRowIDSubstitute, Table &tbl_JOIN_INNER_TD_394_output) {
    // StringRowIDSubstitution: true StringRowIDBackSubstitution: false
    // Supported operation: JOIN_INNER
    // Operation: ListBuffer((s_suppkey#368 = ps_suppkey#330))
    // Left Table: ListBuffer(p_partkey#284, p_mfgr#286, ps_suppkey#330)
    // Right Table: ListBuffer(s_suppkey#368, s_name#369, s_address#370, s_nationkey#371, s_phone#372, s_acctbal#373, s_comment#374)
    // Output Table: ListBuffer(p_partkey#284, p_mfgr#286, s_name#369, s_address#370, s_nationkey#371, s_phone#372, s_acctbal#373, s_comment#374)
    int left_nrow = tbl_JOIN_INNER_TD_4283_output.getNumRow();
    int right_nrow = tbl_SerializeFromObject_TD_4583_input_stringRowIDSubstitute.getNumRow();
    if (left_nrow < right_nrow) { 
        std::unordered_multimap<SW_JOIN_INNER_TD_394_key_leftMajor, SW_JOIN_INNER_TD_394_payload_leftMajor> ht1;
        int nrow1 = tbl_JOIN_INNER_TD_4283_output.getNumRow();
        for (int i = 0; i < nrow1; i++) {
            int32_t _ps_suppkey330_k = tbl_JOIN_INNER_TD_4283_output.getInt32(i, 2);
            SW_JOIN_INNER_TD_394_key_leftMajor keyA{_ps_suppkey330_k};
            int32_t _p_partkey284 = tbl_JOIN_INNER_TD_4283_output.getInt32(i, 0);
            int32_t _p_mfgr286 = tbl_JOIN_INNER_TD_4283_output.getInt32(i, 1);
            int32_t _ps_suppkey330 = tbl_JOIN_INNER_TD_4283_output.getInt32(i, 2);
            SW_JOIN_INNER_TD_394_payload_leftMajor payloadA{_p_partkey284, _p_mfgr286, _ps_suppkey330};
            ht1.insert(std::make_pair(keyA, payloadA));
        }
        int r = 0;
        int nrow2 = tbl_SerializeFromObject_TD_4583_input_stringRowIDSubstitute.getNumRow();
        for (int i = 0; i < nrow2; i++) {
            int32_t _s_suppkey368_k = tbl_SerializeFromObject_TD_4583_input_stringRowIDSubstitute.getInt32(i, 0);
            auto its = ht1.equal_range(SW_JOIN_INNER_TD_394_key_leftMajor{_s_suppkey368_k});
            auto it = its.first;
            while (it != its.second) {
                int32_t _p_partkey284 = (it->second)._p_partkey284;
                int32_t _p_mfgr286 = (it->second)._p_mfgr286;
                int32_t _ps_suppkey330 = (it->second)._ps_suppkey330;
                int32_t _s_suppkey368 = tbl_SerializeFromObject_TD_4583_input_stringRowIDSubstitute.getInt32(i, 0);
                int32_t _s_name369 = tbl_SerializeFromObject_TD_4583_input_stringRowIDSubstitute.getInt32(i, 1);
                int32_t _s_address370 = tbl_SerializeFromObject_TD_4583_input_stringRowIDSubstitute.getInt32(i, 2);
                int32_t _s_nationkey371 = tbl_SerializeFromObject_TD_4583_input_stringRowIDSubstitute.getInt32(i, 3);
                int32_t _s_phone372 = tbl_SerializeFromObject_TD_4583_input_stringRowIDSubstitute.getInt32(i, 4);
                int32_t _s_acctbal373 = tbl_SerializeFromObject_TD_4583_input_stringRowIDSubstitute.getInt32(i, 5);
                int32_t _s_comment374 = tbl_SerializeFromObject_TD_4583_input_stringRowIDSubstitute.getInt32(i, 6);
                tbl_JOIN_INNER_TD_394_output.setInt32(r, 0, _p_partkey284);
                tbl_JOIN_INNER_TD_394_output.setInt32(r, 1, _p_mfgr286);
                tbl_JOIN_INNER_TD_394_output.setInt32(r, 2, _s_name369);
                tbl_JOIN_INNER_TD_394_output.setInt32(r, 3, _s_address370);
                tbl_JOIN_INNER_TD_394_output.setInt32(r, 4, _s_nationkey371);
                tbl_JOIN_INNER_TD_394_output.setInt32(r, 5, _s_phone372);
                tbl_JOIN_INNER_TD_394_output.setInt32(r, 6, _s_acctbal373);
                tbl_JOIN_INNER_TD_394_output.setInt32(r, 7, _s_comment374);
                it++;
                r++;
            }
        }
        tbl_JOIN_INNER_TD_394_output.setNumRow(r);
    } else { 
        std::unordered_multimap<SW_JOIN_INNER_TD_394_key_rightMajor, SW_JOIN_INNER_TD_394_payload_rightMajor> ht1;
        int nrow1 = tbl_SerializeFromObject_TD_4583_input_stringRowIDSubstitute.getNumRow();
        for (int i = 0; i < nrow1; i++) {
            int32_t _s_suppkey368_k = tbl_SerializeFromObject_TD_4583_input_stringRowIDSubstitute.getInt32(i, 0);
            SW_JOIN_INNER_TD_394_key_rightMajor keyA{_s_suppkey368_k};
            int32_t _s_suppkey368 = tbl_SerializeFromObject_TD_4583_input_stringRowIDSubstitute.getInt32(i, 0);
            int32_t _s_name369 = tbl_SerializeFromObject_TD_4583_input_stringRowIDSubstitute.getInt32(i, 1);
            int32_t _s_address370 = tbl_SerializeFromObject_TD_4583_input_stringRowIDSubstitute.getInt32(i, 2);
            int32_t _s_nationkey371 = tbl_SerializeFromObject_TD_4583_input_stringRowIDSubstitute.getInt32(i, 3);
            int32_t _s_phone372 = tbl_SerializeFromObject_TD_4583_input_stringRowIDSubstitute.getInt32(i, 4);
            int32_t _s_acctbal373 = tbl_SerializeFromObject_TD_4583_input_stringRowIDSubstitute.getInt32(i, 5);
            int32_t _s_comment374 = tbl_SerializeFromObject_TD_4583_input_stringRowIDSubstitute.getInt32(i, 6);
            SW_JOIN_INNER_TD_394_payload_rightMajor payloadA{_s_suppkey368, _s_name369, _s_address370, _s_nationkey371, _s_phone372, _s_acctbal373, _s_comment374};
            ht1.insert(std::make_pair(keyA, payloadA));
        }
        int r = 0;
        int nrow2 = tbl_JOIN_INNER_TD_4283_output.getNumRow();
        for (int i = 0; i < nrow2; i++) {
            int32_t _ps_suppkey330_k = tbl_JOIN_INNER_TD_4283_output.getInt32(i, 2);
            auto its = ht1.equal_range(SW_JOIN_INNER_TD_394_key_rightMajor{_ps_suppkey330_k});
            auto it = its.first;
            while (it != its.second) {
                int32_t _s_suppkey368 = (it->second)._s_suppkey368;
                int32_t _s_name369 = (it->second)._s_name369;
                int32_t _s_address370 = (it->second)._s_address370;
                int32_t _s_nationkey371 = (it->second)._s_nationkey371;
                int32_t _s_phone372 = (it->second)._s_phone372;
                int32_t _s_acctbal373 = (it->second)._s_acctbal373;
                int32_t _s_comment374 = (it->second)._s_comment374;
                int32_t _p_partkey284 = tbl_JOIN_INNER_TD_4283_output.getInt32(i, 0);
                int32_t _p_mfgr286 = tbl_JOIN_INNER_TD_4283_output.getInt32(i, 1);
                int32_t _ps_suppkey330 = tbl_JOIN_INNER_TD_4283_output.getInt32(i, 2);
                tbl_JOIN_INNER_TD_394_output.setInt32(r, 2, _s_name369);
                tbl_JOIN_INNER_TD_394_output.setInt32(r, 3, _s_address370);
                tbl_JOIN_INNER_TD_394_output.setInt32(r, 4, _s_nationkey371);
                tbl_JOIN_INNER_TD_394_output.setInt32(r, 5, _s_phone372);
                tbl_JOIN_INNER_TD_394_output.setInt32(r, 6, _s_acctbal373);
                tbl_JOIN_INNER_TD_394_output.setInt32(r, 7, _s_comment374);
                tbl_JOIN_INNER_TD_394_output.setInt32(r, 0, _p_partkey284);
                tbl_JOIN_INNER_TD_394_output.setInt32(r, 1, _p_mfgr286);
                it++;
                r++;
            }
        }
        tbl_JOIN_INNER_TD_394_output.setNumRow(r);
    } 
    std::cout << "tbl_JOIN_INNER_TD_394_output #Row: " << tbl_JOIN_INNER_TD_394_output.getNumRow() << std::endl;
}

struct SW_JOIN_INNER_TD_2792_key_leftMajor {
    int32_t _s_nationkey371;
    bool operator==(const SW_JOIN_INNER_TD_2792_key_leftMajor& other) const {
        return ((_s_nationkey371 == other._s_nationkey371));
    }
};
namespace std {
template <>
struct hash<SW_JOIN_INNER_TD_2792_key_leftMajor> {
    std::size_t operator() (const SW_JOIN_INNER_TD_2792_key_leftMajor& k) const {
        using std::size_t;
        using std::hash;
        using std::string;
        return (hash<int32_t>()(k._s_nationkey371));
    }
};
}
struct SW_JOIN_INNER_TD_2792_payload_leftMajor {
    int32_t _p_partkey284;
    int32_t _p_mfgr286;
    int32_t _s_name369;
    int32_t _s_address370;
    int32_t _s_nationkey371;
    int32_t _s_phone372;
    int32_t _s_acctbal373;
    int32_t _s_comment374;
};
struct SW_JOIN_INNER_TD_2792_key_rightMajor {
    int32_t _n_nationkey164;
    bool operator==(const SW_JOIN_INNER_TD_2792_key_rightMajor& other) const {
        return ((_n_nationkey164 == other._n_nationkey164));
    }
};
namespace std {
template <>
struct hash<SW_JOIN_INNER_TD_2792_key_rightMajor> {
    std::size_t operator() (const SW_JOIN_INNER_TD_2792_key_rightMajor& k) const {
        using std::size_t;
        using std::hash;
        using std::string;
        return (hash<int32_t>()(k._n_nationkey164));
    }
};
}
struct SW_JOIN_INNER_TD_2792_payload_rightMajor {
    int32_t _n_nationkey164;
    int32_t _n_name165;
    int32_t _n_regionkey166;
};
void SW_JOIN_INNER_TD_2792(Table &tbl_JOIN_INNER_TD_394_output, Table &tbl_SerializeFromObject_TD_3961_input_stringRowIDSubstitute, Table &tbl_JOIN_INNER_TD_2792_output) {
    // StringRowIDSubstitution: true StringRowIDBackSubstitution: false
    // Supported operation: JOIN_INNER
    // Operation: ListBuffer((s_nationkey#371 = n_nationkey#164))
    // Left Table: ListBuffer(p_partkey#284, p_mfgr#286, s_name#369, s_address#370, s_nationkey#371, s_phone#372, s_acctbal#373, s_comment#374)
    // Right Table: ListBuffer(n_nationkey#164, n_name#165, n_regionkey#166)
    // Output Table: ListBuffer(p_partkey#284, p_mfgr#286, s_name#369, s_address#370, s_phone#372, s_acctbal#373, s_comment#374, n_name#165, n_regionkey#166)
    int left_nrow = tbl_JOIN_INNER_TD_394_output.getNumRow();
    int right_nrow = tbl_SerializeFromObject_TD_3961_input_stringRowIDSubstitute.getNumRow();
    if (left_nrow < right_nrow) { 
        std::unordered_multimap<SW_JOIN_INNER_TD_2792_key_leftMajor, SW_JOIN_INNER_TD_2792_payload_leftMajor> ht1;
        int nrow1 = tbl_JOIN_INNER_TD_394_output.getNumRow();
        for (int i = 0; i < nrow1; i++) {
            int32_t _s_nationkey371_k = tbl_JOIN_INNER_TD_394_output.getInt32(i, 4);
            SW_JOIN_INNER_TD_2792_key_leftMajor keyA{_s_nationkey371_k};
            int32_t _p_partkey284 = tbl_JOIN_INNER_TD_394_output.getInt32(i, 0);
            int32_t _p_mfgr286 = tbl_JOIN_INNER_TD_394_output.getInt32(i, 1);
            int32_t _s_name369 = tbl_JOIN_INNER_TD_394_output.getInt32(i, 2);
            int32_t _s_address370 = tbl_JOIN_INNER_TD_394_output.getInt32(i, 3);
            int32_t _s_nationkey371 = tbl_JOIN_INNER_TD_394_output.getInt32(i, 4);
            int32_t _s_phone372 = tbl_JOIN_INNER_TD_394_output.getInt32(i, 5);
            int32_t _s_acctbal373 = tbl_JOIN_INNER_TD_394_output.getInt32(i, 6);
            int32_t _s_comment374 = tbl_JOIN_INNER_TD_394_output.getInt32(i, 7);
            SW_JOIN_INNER_TD_2792_payload_leftMajor payloadA{_p_partkey284, _p_mfgr286, _s_name369, _s_address370, _s_nationkey371, _s_phone372, _s_acctbal373, _s_comment374};
            ht1.insert(std::make_pair(keyA, payloadA));
        }
        int r = 0;
        int nrow2 = tbl_SerializeFromObject_TD_3961_input_stringRowIDSubstitute.getNumRow();
        for (int i = 0; i < nrow2; i++) {
            int32_t _n_nationkey164_k = tbl_SerializeFromObject_TD_3961_input_stringRowIDSubstitute.getInt32(i, 0);
            auto its = ht1.equal_range(SW_JOIN_INNER_TD_2792_key_leftMajor{_n_nationkey164_k});
            auto it = its.first;
            while (it != its.second) {
                int32_t _p_partkey284 = (it->second)._p_partkey284;
                int32_t _p_mfgr286 = (it->second)._p_mfgr286;
                int32_t _s_name369 = (it->second)._s_name369;
                int32_t _s_address370 = (it->second)._s_address370;
                int32_t _s_nationkey371 = (it->second)._s_nationkey371;
                int32_t _s_phone372 = (it->second)._s_phone372;
                int32_t _s_acctbal373 = (it->second)._s_acctbal373;
                int32_t _s_comment374 = (it->second)._s_comment374;
                int32_t _n_nationkey164 = tbl_SerializeFromObject_TD_3961_input_stringRowIDSubstitute.getInt32(i, 0);
                int32_t _n_name165 = tbl_SerializeFromObject_TD_3961_input_stringRowIDSubstitute.getInt32(i, 1);
                int32_t _n_regionkey166 = tbl_SerializeFromObject_TD_3961_input_stringRowIDSubstitute.getInt32(i, 2);
                tbl_JOIN_INNER_TD_2792_output.setInt32(r, 0, _p_partkey284);
                tbl_JOIN_INNER_TD_2792_output.setInt32(r, 1, _p_mfgr286);
                tbl_JOIN_INNER_TD_2792_output.setInt32(r, 2, _s_name369);
                tbl_JOIN_INNER_TD_2792_output.setInt32(r, 3, _s_address370);
                tbl_JOIN_INNER_TD_2792_output.setInt32(r, 4, _s_phone372);
                tbl_JOIN_INNER_TD_2792_output.setInt32(r, 5, _s_acctbal373);
                tbl_JOIN_INNER_TD_2792_output.setInt32(r, 6, _s_comment374);
                tbl_JOIN_INNER_TD_2792_output.setInt32(r, 7, _n_name165);
                tbl_JOIN_INNER_TD_2792_output.setInt32(r, 8, _n_regionkey166);
                it++;
                r++;
            }
        }
        tbl_JOIN_INNER_TD_2792_output.setNumRow(r);
    } else { 
        std::unordered_multimap<SW_JOIN_INNER_TD_2792_key_rightMajor, SW_JOIN_INNER_TD_2792_payload_rightMajor> ht1;
        int nrow1 = tbl_SerializeFromObject_TD_3961_input_stringRowIDSubstitute.getNumRow();
        for (int i = 0; i < nrow1; i++) {
            int32_t _n_nationkey164_k = tbl_SerializeFromObject_TD_3961_input_stringRowIDSubstitute.getInt32(i, 0);
            SW_JOIN_INNER_TD_2792_key_rightMajor keyA{_n_nationkey164_k};
            int32_t _n_nationkey164 = tbl_SerializeFromObject_TD_3961_input_stringRowIDSubstitute.getInt32(i, 0);
            int32_t _n_name165 = tbl_SerializeFromObject_TD_3961_input_stringRowIDSubstitute.getInt32(i, 1);
            int32_t _n_regionkey166 = tbl_SerializeFromObject_TD_3961_input_stringRowIDSubstitute.getInt32(i, 2);
            SW_JOIN_INNER_TD_2792_payload_rightMajor payloadA{_n_nationkey164, _n_name165, _n_regionkey166};
            ht1.insert(std::make_pair(keyA, payloadA));
        }
        int r = 0;
        int nrow2 = tbl_JOIN_INNER_TD_394_output.getNumRow();
        for (int i = 0; i < nrow2; i++) {
            int32_t _s_nationkey371_k = tbl_JOIN_INNER_TD_394_output.getInt32(i, 4);
            auto its = ht1.equal_range(SW_JOIN_INNER_TD_2792_key_rightMajor{_s_nationkey371_k});
            auto it = its.first;
            while (it != its.second) {
                int32_t _n_nationkey164 = (it->second)._n_nationkey164;
                int32_t _n_name165 = (it->second)._n_name165;
                int32_t _n_regionkey166 = (it->second)._n_regionkey166;
                int32_t _p_partkey284 = tbl_JOIN_INNER_TD_394_output.getInt32(i, 0);
                int32_t _p_mfgr286 = tbl_JOIN_INNER_TD_394_output.getInt32(i, 1);
                int32_t _s_name369 = tbl_JOIN_INNER_TD_394_output.getInt32(i, 2);
                int32_t _s_address370 = tbl_JOIN_INNER_TD_394_output.getInt32(i, 3);
                int32_t _s_nationkey371 = tbl_JOIN_INNER_TD_394_output.getInt32(i, 4);
                int32_t _s_phone372 = tbl_JOIN_INNER_TD_394_output.getInt32(i, 5);
                int32_t _s_acctbal373 = tbl_JOIN_INNER_TD_394_output.getInt32(i, 6);
                int32_t _s_comment374 = tbl_JOIN_INNER_TD_394_output.getInt32(i, 7);
                tbl_JOIN_INNER_TD_2792_output.setInt32(r, 7, _n_name165);
                tbl_JOIN_INNER_TD_2792_output.setInt32(r, 8, _n_regionkey166);
                tbl_JOIN_INNER_TD_2792_output.setInt32(r, 0, _p_partkey284);
                tbl_JOIN_INNER_TD_2792_output.setInt32(r, 1, _p_mfgr286);
                tbl_JOIN_INNER_TD_2792_output.setInt32(r, 2, _s_name369);
                tbl_JOIN_INNER_TD_2792_output.setInt32(r, 3, _s_address370);
                tbl_JOIN_INNER_TD_2792_output.setInt32(r, 4, _s_phone372);
                tbl_JOIN_INNER_TD_2792_output.setInt32(r, 5, _s_acctbal373);
                tbl_JOIN_INNER_TD_2792_output.setInt32(r, 6, _s_comment374);
                it++;
                r++;
            }
        }
        tbl_JOIN_INNER_TD_2792_output.setNumRow(r);
    } 
    std::cout << "tbl_JOIN_INNER_TD_2792_output #Row: " << tbl_JOIN_INNER_TD_2792_output.getNumRow() << std::endl;
}

struct SW_JOIN_INNER_TD_1987_key_leftMajor {
    int32_t _n_regionkey166;
    bool operator==(const SW_JOIN_INNER_TD_1987_key_leftMajor& other) const {
        return ((_n_regionkey166 == other._n_regionkey166));
    }
};
namespace std {
template <>
struct hash<SW_JOIN_INNER_TD_1987_key_leftMajor> {
    std::size_t operator() (const SW_JOIN_INNER_TD_1987_key_leftMajor& k) const {
        using std::size_t;
        using std::hash;
        using std::string;
        return (hash<int32_t>()(k._n_regionkey166));
    }
};
}
struct SW_JOIN_INNER_TD_1987_payload_leftMajor {
    int32_t _p_partkey284;
    int32_t _p_mfgr286;
    int32_t _s_name369;
    int32_t _s_address370;
    int32_t _s_phone372;
    int32_t _s_acctbal373;
    int32_t _s_comment374;
    int32_t _n_name165;
    int32_t _n_regionkey166;
};
struct SW_JOIN_INNER_TD_1987_key_rightMajor {
    int32_t _r_regionkey188;
    bool operator==(const SW_JOIN_INNER_TD_1987_key_rightMajor& other) const {
        return ((_r_regionkey188 == other._r_regionkey188));
    }
};
namespace std {
template <>
struct hash<SW_JOIN_INNER_TD_1987_key_rightMajor> {
    std::size_t operator() (const SW_JOIN_INNER_TD_1987_key_rightMajor& k) const {
        using std::size_t;
        using std::hash;
        using std::string;
        return (hash<int32_t>()(k._r_regionkey188));
    }
};
}
struct SW_JOIN_INNER_TD_1987_payload_rightMajor {
    int32_t _r_regionkey188;
};
void SW_JOIN_INNER_TD_1987(Table &tbl_JOIN_INNER_TD_2792_output, Table &tbl_Filter_TD_8126_output, Table &tbl_JOIN_INNER_TD_1987_output) {
    // StringRowIDSubstitution: true StringRowIDBackSubstitution: false
    // Supported operation: JOIN_INNER
    // Operation: ListBuffer((n_regionkey#166 = r_regionkey#188))
    // Left Table: ListBuffer(p_partkey#284, p_mfgr#286, s_name#369, s_address#370, s_phone#372, s_acctbal#373, s_comment#374, n_name#165, n_regionkey#166)
    // Right Table: ListBuffer(r_regionkey#188)
    // Output Table: ListBuffer(s_acctbal#373, s_name#369, n_name#165, p_partkey#284, p_mfgr#286, s_address#370, s_phone#372, s_comment#374)
    int left_nrow = tbl_JOIN_INNER_TD_2792_output.getNumRow();
    int right_nrow = tbl_Filter_TD_8126_output.getNumRow();
    if (left_nrow < right_nrow) { 
        std::unordered_multimap<SW_JOIN_INNER_TD_1987_key_leftMajor, SW_JOIN_INNER_TD_1987_payload_leftMajor> ht1;
        int nrow1 = tbl_JOIN_INNER_TD_2792_output.getNumRow();
        for (int i = 0; i < nrow1; i++) {
            int32_t _n_regionkey166_k = tbl_JOIN_INNER_TD_2792_output.getInt32(i, 8);
            SW_JOIN_INNER_TD_1987_key_leftMajor keyA{_n_regionkey166_k};
            int32_t _p_partkey284 = tbl_JOIN_INNER_TD_2792_output.getInt32(i, 0);
            int32_t _p_mfgr286 = tbl_JOIN_INNER_TD_2792_output.getInt32(i, 1);
            int32_t _s_name369 = tbl_JOIN_INNER_TD_2792_output.getInt32(i, 2);
            int32_t _s_address370 = tbl_JOIN_INNER_TD_2792_output.getInt32(i, 3);
            int32_t _s_phone372 = tbl_JOIN_INNER_TD_2792_output.getInt32(i, 4);
            int32_t _s_acctbal373 = tbl_JOIN_INNER_TD_2792_output.getInt32(i, 5);
            int32_t _s_comment374 = tbl_JOIN_INNER_TD_2792_output.getInt32(i, 6);
            int32_t _n_name165 = tbl_JOIN_INNER_TD_2792_output.getInt32(i, 7);
            int32_t _n_regionkey166 = tbl_JOIN_INNER_TD_2792_output.getInt32(i, 8);
            SW_JOIN_INNER_TD_1987_payload_leftMajor payloadA{_p_partkey284, _p_mfgr286, _s_name369, _s_address370, _s_phone372, _s_acctbal373, _s_comment374, _n_name165, _n_regionkey166};
            ht1.insert(std::make_pair(keyA, payloadA));
        }
        int r = 0;
        int nrow2 = tbl_Filter_TD_8126_output.getNumRow();
        for (int i = 0; i < nrow2; i++) {
            int32_t _r_regionkey188_k = tbl_Filter_TD_8126_output.getInt32(i, 0);
            auto its = ht1.equal_range(SW_JOIN_INNER_TD_1987_key_leftMajor{_r_regionkey188_k});
            auto it = its.first;
            while (it != its.second) {
                int32_t _p_partkey284 = (it->second)._p_partkey284;
                int32_t _p_mfgr286 = (it->second)._p_mfgr286;
                int32_t _s_name369 = (it->second)._s_name369;
                int32_t _s_address370 = (it->second)._s_address370;
                int32_t _s_phone372 = (it->second)._s_phone372;
                int32_t _s_acctbal373 = (it->second)._s_acctbal373;
                int32_t _s_comment374 = (it->second)._s_comment374;
                int32_t _n_name165 = (it->second)._n_name165;
                int32_t _n_regionkey166 = (it->second)._n_regionkey166;
                int32_t _r_regionkey188 = tbl_Filter_TD_8126_output.getInt32(i, 0);
                tbl_JOIN_INNER_TD_1987_output.setInt32(r, 3, _p_partkey284);
                tbl_JOIN_INNER_TD_1987_output.setInt32(r, 4, _p_mfgr286);
                tbl_JOIN_INNER_TD_1987_output.setInt32(r, 1, _s_name369);
                tbl_JOIN_INNER_TD_1987_output.setInt32(r, 5, _s_address370);
                tbl_JOIN_INNER_TD_1987_output.setInt32(r, 6, _s_phone372);
                tbl_JOIN_INNER_TD_1987_output.setInt32(r, 0, _s_acctbal373);
                tbl_JOIN_INNER_TD_1987_output.setInt32(r, 7, _s_comment374);
                tbl_JOIN_INNER_TD_1987_output.setInt32(r, 2, _n_name165);
                it++;
                r++;
            }
        }
        tbl_JOIN_INNER_TD_1987_output.setNumRow(r);
    } else { 
        std::unordered_multimap<SW_JOIN_INNER_TD_1987_key_rightMajor, SW_JOIN_INNER_TD_1987_payload_rightMajor> ht1;
        int nrow1 = tbl_Filter_TD_8126_output.getNumRow();
        for (int i = 0; i < nrow1; i++) {
            int32_t _r_regionkey188_k = tbl_Filter_TD_8126_output.getInt32(i, 0);
            SW_JOIN_INNER_TD_1987_key_rightMajor keyA{_r_regionkey188_k};
            int32_t _r_regionkey188 = tbl_Filter_TD_8126_output.getInt32(i, 0);
            SW_JOIN_INNER_TD_1987_payload_rightMajor payloadA{_r_regionkey188};
            ht1.insert(std::make_pair(keyA, payloadA));
        }
        int r = 0;
        int nrow2 = tbl_JOIN_INNER_TD_2792_output.getNumRow();
        for (int i = 0; i < nrow2; i++) {
            int32_t _n_regionkey166_k = tbl_JOIN_INNER_TD_2792_output.getInt32(i, 8);
            auto its = ht1.equal_range(SW_JOIN_INNER_TD_1987_key_rightMajor{_n_regionkey166_k});
            auto it = its.first;
            while (it != its.second) {
                int32_t _r_regionkey188 = (it->second)._r_regionkey188;
                int32_t _p_partkey284 = tbl_JOIN_INNER_TD_2792_output.getInt32(i, 0);
                int32_t _p_mfgr286 = tbl_JOIN_INNER_TD_2792_output.getInt32(i, 1);
                int32_t _s_name369 = tbl_JOIN_INNER_TD_2792_output.getInt32(i, 2);
                int32_t _s_address370 = tbl_JOIN_INNER_TD_2792_output.getInt32(i, 3);
                int32_t _s_phone372 = tbl_JOIN_INNER_TD_2792_output.getInt32(i, 4);
                int32_t _s_acctbal373 = tbl_JOIN_INNER_TD_2792_output.getInt32(i, 5);
                int32_t _s_comment374 = tbl_JOIN_INNER_TD_2792_output.getInt32(i, 6);
                int32_t _n_name165 = tbl_JOIN_INNER_TD_2792_output.getInt32(i, 7);
                int32_t _n_regionkey166 = tbl_JOIN_INNER_TD_2792_output.getInt32(i, 8);
                tbl_JOIN_INNER_TD_1987_output.setInt32(r, 3, _p_partkey284);
                tbl_JOIN_INNER_TD_1987_output.setInt32(r, 4, _p_mfgr286);
                tbl_JOIN_INNER_TD_1987_output.setInt32(r, 1, _s_name369);
                tbl_JOIN_INNER_TD_1987_output.setInt32(r, 5, _s_address370);
                tbl_JOIN_INNER_TD_1987_output.setInt32(r, 6, _s_phone372);
                tbl_JOIN_INNER_TD_1987_output.setInt32(r, 0, _s_acctbal373);
                tbl_JOIN_INNER_TD_1987_output.setInt32(r, 7, _s_comment374);
                tbl_JOIN_INNER_TD_1987_output.setInt32(r, 2, _n_name165);
                it++;
                r++;
            }
        }
        tbl_JOIN_INNER_TD_1987_output.setNumRow(r);
    } 
    std::cout << "tbl_JOIN_INNER_TD_1987_output #Row: " << tbl_JOIN_INNER_TD_1987_output.getNumRow() << std::endl;
}

void SW_Sort_TD_0144(Table &tbl_JOIN_INNER_TD_1987_output, Table &tbl_SerializeFromObject_TD_7781_input, Table &tbl_SerializeFromObject_TD_4583_input, Table &tbl_SerializeFromObject_TD_3961_input, Table &tbl_Sort_TD_0144_output) {
    // StringRowIDSubstitution: false StringRowIDBackSubstitution: true
    // Supported operation: Sort
    // Operation: ListBuffer(s_acctbal#373 DESC NULLS LAST, n_name#165 ASC NULLS FIRST, s_name#369 ASC NULLS FIRST, p_partkey#284 ASC NULLS FIRST)
    // Input: ListBuffer(s_acctbal#373, s_name#369, n_name#165, p_partkey#284, p_mfgr#286, s_address#370, s_phone#372, s_comment#374)
    // Output: ListBuffer(s_acctbal#373, s_name#369, n_name#165, p_partkey#284, p_mfgr#286, s_address#370, s_phone#372, s_comment#374)
    struct SW_Sort_TD_0144Row {
        int32_t _s_acctbal373;
        std::string _s_name369;
        std::string _n_name165;
        int32_t _p_partkey284;
        std::string _p_mfgr286;
        std::string _s_address370;
        std::string _s_phone372;
        std::string _s_comment374;
    }; 

    struct {
        bool operator()(const SW_Sort_TD_0144Row& a, const SW_Sort_TD_0144Row& b) const { return 
 (a._s_acctbal373 > b._s_acctbal373) || 
 ((a._s_acctbal373 == b._s_acctbal373) && (a._n_name165 < b._n_name165)) || 
 ((a._s_acctbal373 == b._s_acctbal373) && (a._n_name165 == b._n_name165) && (a._s_name369 < b._s_name369)) || 
 ((a._s_acctbal373 == b._s_acctbal373) && (a._n_name165 == b._n_name165) && (a._s_name369 == b._s_name369) && (a._p_partkey284 < b._p_partkey284)); 
}
    }SW_Sort_TD_0144_order; 

    int nrow1 = tbl_JOIN_INNER_TD_1987_output.getNumRow();
    std::vector<SW_Sort_TD_0144Row> rows;
    for (int i = 0; i < nrow1; i++) {
        int32_t _s_acctbal373 = tbl_JOIN_INNER_TD_1987_output.getInt32(i, 0);
        std::array<char, TPCH_READ_REGION_LEN + 1> _s_name369 = tbl_SerializeFromObject_TD_3961_input.getcharN<char, TPCH_READ_REGION_LEN + 1>(tbl_JOIN_INNER_TD_1987_output.getInt32(i, 1), 1);
        std::array<char, TPCH_READ_REGION_LEN + 1> _n_name165 = tbl_SerializeFromObject_TD_3961_input.getcharN<char, TPCH_READ_REGION_LEN + 1>(tbl_JOIN_INNER_TD_1987_output.getInt32(i, 2), 1);
        int32_t _p_partkey284 = tbl_JOIN_INNER_TD_1987_output.getInt32(i, 3);
        std::array<char, TPCH_READ_REGION_LEN + 1> _p_mfgr286 = tbl_SerializeFromObject_TD_3961_input.getcharN<char, TPCH_READ_REGION_LEN + 1>(tbl_JOIN_INNER_TD_1987_output.getInt32(i, 4), 1);
        std::array<char, TPCH_READ_REGION_LEN + 1> _s_address370 = tbl_SerializeFromObject_TD_3961_input.getcharN<char, TPCH_READ_REGION_LEN + 1>(tbl_JOIN_INNER_TD_1987_output.getInt32(i, 5), 1);
        std::array<char, TPCH_READ_REGION_LEN + 1> _s_phone372 = tbl_SerializeFromObject_TD_3961_input.getcharN<char, TPCH_READ_REGION_LEN + 1>(tbl_JOIN_INNER_TD_1987_output.getInt32(i, 6), 1);
        std::array<char, TPCH_READ_REGION_LEN + 1> _s_comment374 = tbl_SerializeFromObject_TD_3961_input.getcharN<char, TPCH_READ_REGION_LEN + 1>(tbl_JOIN_INNER_TD_1987_output.getInt32(i, 7), 1);
        SW_Sort_TD_0144Row t = {_s_acctbal373,std::string(_s_name369.data()),std::string(_n_name165.data()),_p_partkey284,std::string(_p_mfgr286.data()),std::string(_s_address370.data()),std::string(_s_phone372.data()),std::string(_s_comment374.data())};
        rows.push_back(t);
    }
    std::sort(rows.begin(), rows.end(), SW_Sort_TD_0144_order);
    int r = 0;
    for (auto& it : rows) {
        tbl_Sort_TD_0144_output.setInt32(r, 0, it._s_acctbal373);
        std::array<char, TPCH_READ_REGION_LEN + 1> _s_name369{};
        memcpy(_s_name369.data(), (it._s_name369).data(), (it._s_name369).length());
        tbl_Sort_TD_0144_output.setcharN<char, TPCH_READ_REGION_LEN +1>(r, 1, _s_name369);
        std::array<char, TPCH_READ_REGION_LEN + 1> _n_name165{};
        memcpy(_n_name165.data(), (it._n_name165).data(), (it._n_name165).length());
        tbl_Sort_TD_0144_output.setcharN<char, TPCH_READ_REGION_LEN +1>(r, 2, _n_name165);
        tbl_Sort_TD_0144_output.setInt32(r, 3, it._p_partkey284);
        std::array<char, TPCH_READ_REGION_LEN + 1> _p_mfgr286{};
        memcpy(_p_mfgr286.data(), (it._p_mfgr286).data(), (it._p_mfgr286).length());
        tbl_Sort_TD_0144_output.setcharN<char, TPCH_READ_REGION_LEN +1>(r, 4, _p_mfgr286);
        std::array<char, TPCH_READ_REGION_LEN + 1> _s_address370{};
        memcpy(_s_address370.data(), (it._s_address370).data(), (it._s_address370).length());
        tbl_Sort_TD_0144_output.setcharN<char, TPCH_READ_REGION_LEN +1>(r, 5, _s_address370);
        std::array<char, TPCH_READ_REGION_LEN + 1> _s_phone372{};
        memcpy(_s_phone372.data(), (it._s_phone372).data(), (it._s_phone372).length());
        tbl_Sort_TD_0144_output.setcharN<char, TPCH_READ_REGION_LEN +1>(r, 6, _s_phone372);
        std::array<char, TPCH_READ_REGION_LEN + 1> _s_comment374{};
        memcpy(_s_comment374.data(), (it._s_comment374).data(), (it._s_comment374).length());
        tbl_Sort_TD_0144_output.setcharN<char, TPCH_READ_REGION_LEN +1>(r, 7, _s_comment374);
        if (r < 10) {
            std::cout << it._s_acctbal373 << " " << (it._s_name369).data() << " " << (it._n_name165).data() << " " << it._p_partkey284 << " " << (it._p_mfgr286).data() << " " << (it._s_address370).data() << " " << (it._s_phone372).data() << " " << (it._s_comment374).data() << " " << std::endl;
        }
        ++r;
    }
    tbl_Sort_TD_0144_output.setNumRow(r);
    std::cout << "tbl_Sort_TD_0144_output #Row: " << tbl_Sort_TD_0144_output.getNumRow() << std::endl;
}

