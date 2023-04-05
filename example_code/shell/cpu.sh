#! /bin/bash
PID=18493

while getopts "p:" option
do
    case "$option" in
        p)
        PID=$OPTARG
        ;;
        :|\?)
        echo "invalid option: '$option'"
        exit 1;
        ;;
    esac
done

cpu_core_num=`cat /proc/cpuinfo|grep processor|wc|awk '{print $1}'`

print_process_cpu_precent()
{
    cpu_total_time1=`cat /proc/stat | head -n1 |awk '{print $2+$3+$4+$5+$6+$7+$8}'`
    process_time1=`cat /proc/${PID}/stat | head -n1 | awk '{print $14+$15+$16+$17}'`
    sleep 1

    cpu_total_time2=`cat /proc/stat | head -n1 |awk '{print $2+$3+$4+$5+$6+$7+$8}'`
    process_time2=`cat /proc/${PID}/stat | head -n1 | awk '{print $14+$15+$16+$17}'`

    cpu_time=$((cpu_total_time2 - cpu_total_time1))
    process_time=$((process_time2 - process_time1))

    cpu_percent=$((100 * process_time * cpu_core_num / cpu_time))

    echo "process : $PID, cpu percent : $cpu_percent"
}

print_cpu_precent()
{
    n=1
    while [ $n -le $cpu_core_num ]
    do
        cpu_total_time1=`cat /proc/stat | head -${n} |awk '{print $2+$3+$4+$5+$6+$7+$8}' | tail -1`
        cpu_user_time1=`cat /proc/stat | head -${n} |awk '{print $2}' | tail -1`
        cpu_sys_time1=`cat /proc/stat | head -${n} |awk '{print $4}' | tail -1`

        sleep 0.2
        cpu_total_time2=`cat /proc/stat | head -${n} |awk '{print $2+$3+$4+$5+$6+$7+$8}' | tail -1`
        cpu_user_time2=`cat /proc/stat | head -${n} |awk '{print $2}' | tail -1`
        cpu_sys_time2=`cat /proc/stat | head -${n} |awk '{print $4}' | tail -1`

        cpu_time=$((cpu_total_time2 - cpu_total_time1))
        user_time=$((cpu_user_time2 - cpu_user_time1))
        sys_time=$((cpu_sys_time2 - cpu_sys_time1))

        cpu_user_percent=$((100 * user_time / cpu_time))
        cpu_sys_percent=$((100 * sys_time / cpu_time))

        echo "[cpu $n] user percent : $cpu_user_percent, syc percent $cpu_sys_percent"

        let n++
    done
    sleep 1
}

while((1))
do
print_process_cpu_precent
print_cpu_precent
done