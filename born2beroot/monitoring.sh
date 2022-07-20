arch=$(uname -a)
pcpu=$(lscpu -b -p=Core,Socket | grep -v '^#' | sort -u | wc -l)
vcpu=$(cat /proc/cpuinfo | grep processor | wc -l)
usedmem=$(free -m | awk 'FNR == 2 {print $3}')
totalmem=$(free -m | awk 'FNR == 2 {print $2}')
memusage=$(free | grep Mem | awk '{printf("%.2f"), $3/$2 * 100}')
useddsk=$(df -Bm | grep '^/dev/' | grep -v '/boot$' | awk '{u += $3} END {print u}')
totaldsk=$(df -Bg | grep '^/dev' | grep -v '/boot$' | awk '{t += $2} END {print t}')
dskusage=$(df -Bm | grep '^/dev' | grep -v '/boot$' | awk '{u += $3} {t += $2} END {printf("%d"), u/t * 100}')
cpuuse=$(top -bn1 | grep "Cpu(s)" | cut -c 9- | xargs | awk '{printf("%.1f"), $1+$3}')
lastboot=$(who -b | awk '{print $3 " " $4}')
lvmstate=$(lsblk | awk '$6 == "lvm"' | if [[ $(wc -l) > 0 ]]; then echo yes; else echo no; fi)
tcpc=$(ss -s | grep "estab" | xargs | awk -F"[, \t]" '{print $4}')
usrlog=$(users | wc -w)
ip=$(hostname -I | awk -F"[ \t]" '{print $1}')
mac=$(ip link show | grep "link/ether" | awk '{print $2}')
sudo=$(journalctl -q _COMM=sudo | grep COMMAND | wc -l)
wall "	#Architecture : $arch
	#CPU physical : $pcpu
	#CPU virtual : $vcpu
	#Memory Usage : ${usedmem}/${totalmem}MB (${memusage}%)
	#Disk Usage : ${useddsk}/${totaldsk}Gb (${dskusage}%)
	#CPU Load : ${cpuuse}%
	#Last boot : $lastboot
	#LVM use : $lvmstate
	#TCP Connections : $tcpc
	#User log : $usrlog
	#Network IP : $ip ($mac)
	#Sudo : $sudo"
