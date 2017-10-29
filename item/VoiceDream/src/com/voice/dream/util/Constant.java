package com.voice.dream.util;

public class Constant {
	
	public static final class DebugConfig {
		// ���ϻ���Ի���
		public static boolean ONLINE_SERVER = true;
		
		public static String SERVER_URL = "www.baidu.com";
		
		public static long DEFAULT_CONNECT_TIMEOUT=15*1000;
		
		public static boolean SHOW_NET_INFO = true;
		
		// web�˿�
		public static String SERVER_PORT = ONLINE_SERVER ? "80" : "8081";
		
		public static String logDir = "DuoBaoDream";
	    public static String logFile = "duoBaoAppLog.txt";
	    
	 // ���Կ���̨��־
		public static final boolean DEBUG = true;
		public static final boolean CLOG = false;

		// �Ƿ��ӡlog
		public static final boolean LOG_ENABLE = DEBUG;
		// �Ƿ񵯳�����toast
		public static final boolean TOAST_ENABLE = DEBUG;

		// �Ƿ���ʾ��Ļ�ϵ�log������
		public static final boolean LOGVIEW_ENABLE = DEBUG;

		// �Ƿ�LOGд��sd��
		public static final boolean LOG2SD_ENABLE = DEBUG;
	    
	}
	
}
