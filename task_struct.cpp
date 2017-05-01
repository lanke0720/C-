struct task_struct {
	long state;	 //����Ľ���״̬��-1 �������У�0 �����У���������>0 ��ֹͣ��
	long counter;//��������ʱ��������ݼ����δ�����������ʱ��Ƭ
	long priority;//�������ȼ�������ʼ����ʱcount = priority��Խ������Խ��
	long signal;//�źţ���λͼ��ÿ������λ����һ���źţ��ź�ֵ = λƫ��ֵ+1
	fn_ptr sig_restorer;
	fn_ptr sig_fn[32];

	int exit_code; //����ִ��ֹͣ���˳��룬�丸���̻�ȡ
	unsigned long end_code,end_data,brk,start_stack;
	//���볤�ȣ��ֽڣ������볤��+���ݳ��ȣ��ֽڣ����ܳ��ȣ��ֽڣ�����ջ�ε�ַ��
	long pid,father,pgrp,session,leader;
	//���̱�ʶ�ţ����̺ţ��������̺ţ���������ţ��ػ��ţ��ػ����졣
	unsigned short uid,euid,suid;
	//�û���ʶ�ţ��û�ID������Ч�û�ID��������û�ID
	unsigned short gid,egid,sgid;
	long alarm; //������ʱֵ���δ�����
	long utime,stime,cutime,cstime,start_time;
	//�û�̬����ʱ�䣬ϵͳ̬����ʱ��,�ӽ����û�̬����ʱ�䣬�ӽ���ϵͳ̬����ʱ�䣬
	// ���̿�ʼ����ʱ�̣�

	unsigned short used_math;//��־���Ƿ�ʹ����Э������
	int tty;  //����ʹ��tty �����豸�ţ�-1��ʾû��ʹ�á�

	unsigned short umask; //�ļ�������������λ��
	struct m_inode * pwd; //��ǰ����Ŀ¼i���ṹ��
	struct m_inode * root; //��Ŀ¼ i �ڵ�ṹ
	unsigned long close_on_exec;// ִ��ʱ�ر��ļ����ͼ��־��include/fcntl.h��
	struct file * filp[NR_OPEN]; //����ʹ�õ��ļ���ṹ
	struct desc_struct ldt[3];//������ľֲ�����������0-�գ�1-�����cs��2-���ݺͶ�ջ��ds&ss
	struct tss_struct tss; //�����̵�����״̬��Ϣ�ṹ
};