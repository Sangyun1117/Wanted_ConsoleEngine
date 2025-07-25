#pragma
#include "Core.h"
#include "Math/Vector2.h"
#include "RTTI.h"

//��ü ���ؾ��ұ�?
//��ġ ����
//�ܼ� â�� �׸���(How?What?).
//������ �̺�Ʈ �Լ� ȣ��
//BeginPlay/Tick/Draw

//����
enum class Color : int {
	Blue = 1,
	Green = 2,
	Red = 4,
	White = Red | Green | Blue, //7
	Intensity = 8,
};
class Engine_API Actor : public RTTI
{
	RTTI_DECLARATIONS(Actor, RTTI) //;���̸� �ȵ�. �Լ�ȣ�� �ƴ�
public:
	Actor(const char image = ' ', Color color = Color::White);
	virtual ~Actor();

	//�̺�Ʈ �Լ�

	//��ü �����ֱ�(Lifetime)�� 1���� ȣ���(�ʱ�ȭ ����)
	virtual void BeginPlay();
	//������ ���� ȣ��(�ݺ��� �۾�/ ���Ӽ��� �ʿ��� �۾�)
	virtual void Tick(float deltaTime);
	//�׸��� �Լ�
	virtual void Render();
	//BeginPlay ȣ�� ���� Ȯ��
	inline bool HasBeginPlay() const { return hasBeginPlay; }
	//��ġ ����/ �� �д� �Լ�
	void SetPosition(const Vector2& newPosition);
	Vector2 Position() const;
private:
	//��ü�� ��ġ.
	Vector2 position;

	//�׸� ��
	char image = ' ';

	Color color;

	//BeginPlay ȣ���� �Ǿ����� Ȯ��
	bool hasBeginPlay = false;
};













