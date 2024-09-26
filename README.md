# SQL2FPGA: Automatic Acceleration of SQL Query Processing on Modern CPU-FPGA Platforms

This repository includes the code for SQL2FPGA. SQL2FPGA is a hardware-aware SQL query compilation framwork for translating and efficiently mapping SQL queries on the modern heterogeneous CPU-FPGA platforms. SQL2FPGA takes the optimized query execution plans of SQL queries from big data query processing engines (Spark SQL for now); performs hardware-aware optimizations to map query operations to FPGA accelerators (AMD/Xilinx Vitis database overlays for now); and lastly generates the deployable CPU host code and the associated FPGA accelerator configuration code. 

If you find this project useful in your research, please consider citing:

    @inproceedings{lu2023sql2fpga,
      title={SQL2FPGA: Automatic Acceleration of SQL Query Processing on Modern CPU-FPGA Platforms},
      author={Lu, Alec and Fang, Zhenman},
      booktitle={Proceedings of the 31st IEEE International Symposium On Field-Programmable Custom Computing Machines},
      year={2023}
    }

## Download SQL2FPGA
```
git clone https://github.com/SFU-HiAccel/SQL2FPGA.git
```

## Environmental Setup
1. **Hardware platforms (evaluated):**
    * **Host CPU:**
      * 64-bit Ubuntu 18.04.2 LTS
    * **FPGA Accelerator Design:**
      * [Xilinx Database Library 2020.1](https://github.com/Xilinx/Vitis_Libraries/tree/2020.1/database)
    * **FPGA:**
      * Xilinx Alveo U280

2. **Software tools (evaluated):**
    * **Big data query processing tool:**
      * Spark 3.1.1
    * **HLS tool:**
      * Vitis 2020.1
      * Xilinx Runtime(XRT) 2020.1

## Accelerate SQL Query Processing using SQL2FPGA
1. Import SQL2FPGA Project using IntelliJ
    * Install `Scala` plugin
    * Open project ...
    * Select `pom.xml` project file
    * Select Scala version to match 2.13
    * Build module `SQL2FPGA_Top`
    * You can also execute 'mvn package && java -jar target/SQL2FPGA-1.0-SNAPSHOT-jar-with-dependencies.jar' to run the main function.

2. Run SQL2FPGA Project on TPC-H Dataset
    * Download TPC-H Benchmark Generator
        ```
        git clone https://github.com/electrum/tpch-dbgen.git
        ```
    * Generate TPC-H Dataset (our evaluation covers SF1 and SF30)
        ```
        cd tpch-dbgen/
        make
        ./dbgen -s <#> 
        ```
    * Generate TPC_DS Dataset
        ```
        git clone https://github.com/gregrahn/tpcds-kit.git
        cd tpcds-kit/tools
        make OS=LINUX

        ```
        check https://github.com/gregrahn/tpcds-kit for detailed tutorial.

    * Specifiy Query Configurations (in `SQL2FPGA_Top.scala`)
        * Specify Dataset File Path
            * Modify `INPUT_DIR_TPCH` and `OUTPUT_DIR_TPCH` with the generated TPC-H dataset
        * Query Specifications
            * Modify `qConfig.tpch_queryNum_start` and `qConfig.tpch_queryNum_end` to specifiy the range of queries to generate code
        * Execution Mode
            * `qConfig.pure_sw_mode = 1` indicates all operators are executed on CPU and `qConfig.pure_sw_mode = 0` indicates a hybrid execution mode where both CPU and FPGA accelerators are used for execution 
            * `qConfig.scale_factor = 1` specifies the scale factor (SF)
    * Build and Run SQL2FPGA Module
       * Build and run module `SQL2FPGA_Top`
    * Output:
       * CPU Host Code: `test_q#.cpp` 
       * FPGA Configuration Code: `cfgFunc_q#.hpp`
       * SW Operator Function Code: `q#.hpp`

3. Build AMD-Xilinx's Database Accelerator Overlay Designs
    * Clone AMD-Xilinx's Vitis Libraries: 
        ```
        git clone https://github.com/Xilinx/Vitis_Libraries.git
        ```
    * Switch to the `2020.1` branch
        ```
        cd Vitis_Libraries
        git checkout 2020.1
        ```
    * Build gqeJoin and gqeAggr accelerator overlay designs (this will take more than 10 hours to finish)
        ```
        cd database/L2/demos
        make -C build_join_partition/ TARGET=hw xclbin DEVICE=xilinx_u280_xdma_201920_3
        make -C build_aggr_partition/ TARGET=hw xclbin DEVICE=xilinx_u280_xdma_201920_3
        ```
    * If you encounter the problem 'Failed to create IP', it is a bug in Vitis XRT, you can run 
        ```
        faketime -f "-10y"  make -C build_join_partition/ TARGET=hw xclbin DEVICE=/opt/xilinx/platforms/xilinx_aliyun-f3_dynamic_5_0/xilinx_aliyun-f3_dynamic_5_0.xpfm &
        ```
        to skip the bug.
        
4. Run SQL2FPGA-generated Designs on Device
    * Replace `makefile` at `/Vitis_Libraries/database/L2/demos` with the  `<$SQL2FPGA_HOME>/makefile`
    * Move SQL2FPGA generated code to `/Vitis_Libraries/database/L2/demos/host/q#/sfsql2fpga_fpga`
    * Compile and execute the design at `/Vitis_Libraries/database/L2/demos`
        ```
        make clean
        make run TARGET=hw MODE=FPGA TB=Q# DEVICE=xilinx_u280_xdma_201920_3 TEST=SQL2FPGA
        ```
## files need to add in gqe-api.hpp in Vitis Library

```
   void copyTableData(Table* dest_table) {
        int cpNum = 0;
        for (size_t i = 0; i < ncol; i++) {
            if (iskdata[i] == 1) {
                cpNum++;
            }
        }
        size_t depth = nrow + VEC_LEN * 2 - 1;
        size_t sizeonecol = size_t((4 * depth + 64 - 1) / 64);

        size_t numBytes = 0;
        if (getKdata()) {
            numBytes = 64  sizeonecol  cpNum;
            memcpy((char*)dest_table->datak, (char*)datak, numBytes);
        } else {
            numBytes = 64 * size512.back();
            memcpy((char*)dest_table->data, (char*)data, numBytes);
        }
    };

```


Now you have compeletd the entire tool flow of SQL2FPGA. Hack the code and have fun!

## Known Limitations
* Whether to use hash partition logic requires manual specification in SF30.
* Device selection between CPU and FPGA overlay design is currently manually selected through empirical results.
* Output table size required manual input to achieve the best CPU-to-FPGA memory transfer time.



## Authors and Contributors
SQL2FPGA is currently maintained by [Alec Lu](http://www.sfu.ca/~fla30/).

Besides, we thank AMD-Xilinx Vitis DB team, Prof. Jiannan Wang and Dr. Jinglin Peng from Simon Fraser University, for their insightful discussion and technical support.

## Papers
More implementation details of SQL2FPGA are covered in [our paper](http://www.sfu.ca/~fla30/papers/C9_FCCM_2023_SQL2FPGA.pdf).
