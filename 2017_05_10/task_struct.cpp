struct task_struct {
	long state;	 //任务的进行状态（-1 不可运行，0 可运行（就绪），>0 已停止）
	long counter;//任务运行时间计数（递减，滴答数），运行时间片
	long priority;//运行优先级，任务开始运行时count = priority，越大运行越长
	long signal;//信号，是位图，每个比特位代表一种信号，信号值 = 位偏移值+1
	fn_ptr sig_restorer;
	fn_ptr sig_fn[32];

	int exit_code; //任务执行停止的退出码，其父进程会取
	unsigned long end_code,end_data,brk,start_stack;
	//代码长度（字节），代码长度+数据长度（字节），总长度（字节），堆栈段地址。
	long pid,father,pgrp,session,leader;
	//进程标识号（进程号），父进程号，父进程组号，回话号，回话首领。
	unsigned short uid,euid,suid;
	//用户标识号（用户ID），有效用户ID，保存的用户ID
	unsigned short gid,egid,sgid;
	long alarm; //报警定时值（滴答数）
	long utime,stime,cutime,cstime,start_time;
	//用户态运行时间，系统态运行时间,子进程用户态运行时间，子进程系统态运行时间，
	// 进程开始运行时刻；

	unsigned short used_math;//标志：是否使用了协处理器
	int tty;  //进程使用tty 的子设备号，-1表示没有使用。

	unsigned short umask; //文件创建属性屏蔽位；
	struct m_inode * pwd; //当前工作目录i结点结构。
	struct m_inode * root; //根目录 i 节点结构
	unsigned long close_on_exec;// 执行时关闭文件句柄图标志（include/fcntl.h）
	struct file * filp[NR_OPEN]; //进程使用的文件表结构
	struct desc_struct ldt[3];//本任务的局部表描述符。0-空，1-代码段cs，2-数据和堆栈段ds&ss
	struct tss_struct tss; //本进程的任务状态信息结构
};