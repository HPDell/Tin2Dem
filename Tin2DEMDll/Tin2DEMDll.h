// ���� ifdef ���Ǵ���ʹ�� DLL �������򵥵�
// ��ı�׼�������� DLL �е������ļ��������������϶���� TIN2DEMDLL_EXPORTS
// ���ű���ġ���ʹ�ô� DLL ��
// �κ�������Ŀ�ϲ�Ӧ����˷��š�������Դ�ļ��а������ļ����κ�������Ŀ���Ὣ
// TIN2DEMDLL_API ������Ϊ�Ǵ� DLL ����ģ����� DLL ���ô˺궨���
// ������Ϊ�Ǳ������ġ�
#ifdef TIN2DEMDLL_EXPORTS
#define TIN2DEMDLL_API __declspec(dllexport)
#else
#define TIN2DEMDLL_API __declspec(dllimport)
#endif

// �����Ǵ� Tin2DEMDll.dll ������
class TIN2DEMDLL_API CTin2DEMDll {
public:
	CTin2DEMDll(void);
	// TODO:  �ڴ�������ķ�����
};

extern TIN2DEMDLL_API int nTin2DEMDll;

TIN2DEMDLL_API int fnTin2DEMDll(void);
