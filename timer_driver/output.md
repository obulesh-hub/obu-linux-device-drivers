obu@obu-VirtualBox:~/Desktop/obu-linux-device-drivers/timer_driver$ sudo su
[sudo] password for obu: 
root@obu-VirtualBox:/home/obu/Desktop/obu-linux-device-drivers/timer_driver# insmod timer_driver.ko 
root@obu-VirtualBox:/home/obu/Desktop/obu-linux-device-drivers/timer_driver# dmesg | tail -20
[ 8661.643559] Obu Timer Callback executed at jiffies=4303326080
[ 8663.690147] Obu Timer Callback executed at jiffies=4303328128
[ 8665.737577] Obu Timer Callback executed at jiffies=4303330176
[ 8667.784567] Obu Timer Callback executed at jiffies=4303332224
[ 8669.831742] Obu Timer Callback executed at jiffies=4303334272
[ 8671.878274] Obu Timer Callback executed at jiffies=4303336320
[ 8673.926145] Obu Timer Callback executed at jiffies=4303338368
[ 8675.972144] Obu Timer Callback executed at jiffies=4303340416
[ 8678.019851] Obu Timer Callback executed at jiffies=4303342464
[ 8680.066404] Obu Timer Callback executed at jiffies=4303344512
[ 8682.113146] Obu Timer Callback executed at jiffies=4303346560
[ 8684.160329] Obu Timer Callback executed at jiffies=4303348608
[ 8686.212542] Obu Timer Callback executed at jiffies=4303350661
[ 8686.482191] Obu Timer Module Loaded
[ 8688.255837] Obu Timer Callback executed at jiffies=4303352705
[ 8688.464140] Obu Timer Callback executed at jiffies=4303352913 (~4303352 sec)
[ 8690.301403] Obu Timer Callback executed at jiffies=4303354752
[ 8690.493063] Obu Timer Callback executed at jiffies=4303354944 (~4303354 sec)
[ 8692.349051] Obu Timer Callback executed at jiffies=4303356801
[ 8692.539816] Obu Timer Callback executed at jiffies=4303356992 (~4303356 sec)

