!/bin/bash

# Call a test here.
echo "executing rsm mem initial value test no 1"
echo $PROJECT_HOME
cd $PROJECT_HOME/tests/mem_access/rcs_mem/rcs_rsm/rsm_mem_initial_value_test
make clean
make
python rsm_mem_initial_value_test.py

echo "executing rsm mem write read test no 2"
cd $PROJECT_HOME/tests/mem_access/rcs_mem/rcs_rsm/rsm_mem_write_read_test
make clean
make
python rsm_mem_write_read_test.py

echo "executing core calib initial value test no 3"
cd $PROJECT_HOME/tests/mem_access/rcs_mem/rcs_core_calib/core_calib_mem_initial_value_test
make clean
make
python core_calib_mem_initial_value_test.py 


echo "executing core calib write read memory test no 4"
cd $PROJECT_HOME/tests/mem_access/rcs_mem/rcs_core_calib/core_calib_mem_write_read_test
make clean
make
python core_calib_mem_write_read_test.py 


echo "executing core ctrl initial value test no 5"
cd $PROJECT_HOME/tests/mem_access/rcs_mem/rcs_core_ctrl/core_ctrl_mem_initial_value_test
make clean
make
python core_ctrl_mem_initial_value_test.py 


echo "executing core ctrl write read test no 6"
cd $PROJECT_HOME/tests/mem_access/rcs_mem/rcs_core_ctrl/core_ctrl_mem_write_read_test
make clean
make
python core_ctrl_mem_write_read_test.py 



echo "executing drf mem initial value test no 7"
cd $PROJECT_HOME/tests/mem_access/drf_mem/drf_mem_initial_value
make clean
make
python drf_mem_initial_value.py 

echo "executing drf mem write read test no 8"
cd $PROJECT_HOME/tests/mem_access/drf_mem/drf_mem_write_read
make clean
make
python drf_mem_write_read.py 

echo "executing vex mem initial value test no 9"
cd $PROJECT_HOME/tests/mem_access/vex_mem/initial_test/dmem_mem_initial_value_test
make clean
make
python dmem_mem_initial_value_test.py 

echo "executing vex mem write read test no 10"
cd $PROJECT_HOME/tests/mem_access/vex_mem/write_read/dmem_mem_write_read_test
make clean
make
python dmem_mem_write_read_test.py 

echo "executing vex mem initial value test no 9"
cd $PROJECT_HOME/tests/mem_access/vex_mem/initial_test/vmem_mem_initial_value_test
make clean
make
python vmem_mem_initial_value_test.py 

echo "executing vex mem write read test no 10"
make clean
make
python vmem_mem_write_read_test.py 

echo "executing vex mem initial value test no 11"
cd $PROJECT_HOME/tests/mem_access/vex_mem/initial_value_test/pmem_mem_initial_value_test
make clean
make
python pmem_mem_initial_value_test.py 

echo "executing vex mem write read test no 12"
cd $PROJECT_HOME/tests/mem_access/vex_mem/write_read/pmem_mem_write_read_test
make clean
make
python pmem_mem_write_read_test.py 
