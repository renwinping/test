#!/bin/awk -f

##
#
# ��notice log �в鿴cmatch_ad_src_type �� �Ƿ�������ĳ�����Դ
#
#
# author: zm 2015��5��12��14:04:25
#

BEGIN {
	FS=" "
}

{
	for (i = 1; i < NF; i++)
	{
		if (match($i, "cmatch_ad_src_type") && split($i, a, "=") == 2)
		{
			if (split(a[2], b, ",") == 2 && match(b[2], "8"))
			{		
				printf("%s\n", $0);
				break;
			}
		}
	}
}
