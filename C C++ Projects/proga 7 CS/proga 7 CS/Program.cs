using namespace System;
using namespace System::IO; 
using namespace System::Text;

public delegate void MethodCafedra7(int CafedraSize);
public delegate void MethodGroup5(String^ group, int GroupSize);

int CafedraSIZE = 0;

ref class Student
{
    public:
    String^ StudentName;
    int number;
    void SetStudent()
    {
        Console::WriteLine("Введите имя студента:");
        StudentName = Convert::ToString(Console::ReadLine());
    }
};

template<class ObjType>
ref class Group
{
    public:
    event MethodCafedra7^ Cafedra;
    event MethodGroup5^ Student;
    String^ GroupName;
    cli::array < ObjType^ >^ Students;
    int size;
    Group()
    {
        Console::WriteLine("Введите название группы:");
        GroupName = Convert::ToString(Console::ReadLine());
        size = 0;
        Students = gcnew cli::array < ObjType ^ > (size);
    }
    void AddNewStudent()
    {
        size += 1;
        cli::array < ObjType ^ > ^temp = gcnew cli::array < ObjType ^ > (size);
        for (int i = 0; i < size; i++)
        {
            if (i == size - 1)
            {
                temp[size - 1] = gcnew ObjType;
                temp[size - 1]->number = (size - 1);
                temp[size - 1]->SetStudent();
            }
            else
            {
                temp[i] = gcnew ObjType;
                temp[i] = Students[i];
            }
        }
        delete Students;
        Students = gcnew cli::array < ObjType ^ > (size);
        for (int i = 0; i < size; i++)
        {
            Students[i] = gcnew ObjType;
            Students[i] = temp[i];
        }
        delete temp;
        CafedraSIZE++;
        if (size > 5)
        {
            Student(GroupName, size);
        }
        if (CafedraSIZE < 7)
        {
            Cafedra(CafedraSIZE);
        }
    }
    void DeleteStudent(int number)
    {
        size -= 1;
        cli::array < ObjType ^ > ^temp = gcnew cli::array < ObjType ^ > (size);
        for (int i = 0; i < size; i++)
        {
            if (i < number)
            {
                temp[i] = gcnew ObjType;
                temp[i] = Students[i];
            }
            else if (i > number)
            {
                temp[i] = gcnew ObjType;
                temp[i] = Students[i];
                Students[i]->number -= 1;
            }
            else if (number + 1 == size)
            {
                temp[i] = gcnew ObjType;
                temp[i] = Students[i + 1];
                Students[i + 1]->number -= 1;
            }
        }
        delete Students;
        Students = gcnew cli::array < ObjType ^ > (size);
        for (int i = 0; i < size; i++)
        {
            Students[i] = gcnew ObjType;
            Students[i] = temp[i];
        }
        delete temp;
        CafedraSIZE--;
        if (CafedraSIZE < 7)
        {
            Cafedra(CafedraSIZE);
        }
    }
    void GetGroup()
    {
        for (int i = 0; i < size; i++)
        {
            Console::WriteLine("Группа:\t" + GroupName + "\tНомер:\t" + Students[i]->number + "\tИмя:\t" + Students[i]->StudentName);
        }
    }
};

ref class EventMessages
{
    public:
    void Group5(String^ GroupName, int size)
    {
        Console::WriteLine("Студентов в группе " + GroupName + " больше 5. Всего в группе " + size + " студентов\n");
        Console::WriteLine("Нажмите Enter...");
        Console::ReadKey();
    }
    void Cafedra7(int CafedraSize)
    {
        Console::WriteLine("На кафедре меньше 7 студентов. А именно - " + CafedraSize + " студентов\n");
        Console::WriteLine("Нажмите Enter...");
        Console::ReadKey();
    }
};

ref class Statistics
{
    public:
    Statistics()
    {
        IO::File::WriteAllText("statistics.txt", "Отчёт по событиям\n");
    }
    void Group5(String^ GroupName, int size)
    {
        String ^ Message = "Студентов в группе " + GroupName + " больше 5. Всего в группе " + size + " студентов\n";
        IO::File::AppendAllText("statistics.txt", Message);
    }
    void Cafedra7(int CafedraSize)
    {
        String ^ Message = "На кафедре меньше 7 студентов. А именно - " + CafedraSize + " студентов\n";
        IO::File::AppendAllText("statistics.txt", Message);
    }
};

int main()
{
    int amount, menu;

    Console::OutputEncoding = System::Text::Encoding::UTF8;
    Console::Clear();

    Console::WriteLine("Введите количество групп на кафедре:");
    amount = Convert::ToInt32(Console::ReadLine());

    cli::array < Group<Student> ^> ^CAFEDRA = gcnew cli::array < Group<Student> ^> (amount);

    for (int i = 0; i < amount; i++)
    {
        CAFEDRA[i] = gcnew Group<Student>;
    }

    EventMessages ^ MESSAGE = gcnew EventMessages();
    Statistics ^ FILE = gcnew Statistics();

    for (int i = 0; i < amount; i++)
    {
        CAFEDRA[i]->Cafedra += gcnew MethodCafedra7(MESSAGE, &EventMessages::Cafedra7);
        CAFEDRA[i]->Cafedra += gcnew MethodCafedra7(FILE, &Statistics::Cafedra7);
        CAFEDRA[i]->Student += gcnew MethodGroup5(MESSAGE, &EventMessages::Group5);
        CAFEDRA[i]->Student += gcnew MethodGroup5(FILE, &Statistics::Group5);
    }

    while (true)
    {
        Console::Clear();
        for (int i = 0; i < amount; i++)
        {
            CAFEDRA[i]->GetGroup();
        }
        Console::WriteLine("Выберите функцию:\n1 - добавить студента\t2 - удалить студента");
        menu = Convert::ToInt32(Console::ReadLine());
        switch (menu)
        {
            case 1:
                {
                    String ^ name;
                    Console::WriteLine("Введите название группы для добавления студента:");
                    name = Convert::ToString(Console::ReadLine());
                    for (int i = 0; i < amount; i++)
                    {
                        if (CAFEDRA[i]->GroupName == name)
                        {
                            CAFEDRA[i]->AddNewStudent();
                        }
                    }
                    break;
                }
            case 2:
                {
                    String ^ name;
                    Console::WriteLine("Введите название группы для удаления студента:");
                    name = Convert::ToString(Console::ReadLine());
                    for (int i = 0; i < amount; i++)
                    {
                        if (CAFEDRA[i]->GroupName == name)
                        {
                            int number;
                            Console::WriteLine("Введите номер студента для удаления:");
                            number = Convert::ToInt32(Console::ReadLine());
                            CAFEDRA[i]->DeleteStudent(number);
                        }
                    }
                    break;
                }
            default:
                Console::WriteLine("Выберите существующую функцию!");
                Console::Clear();
                break;
        }
    }
}
