using namespace System;
using namespace System::IO;
using namespace System::Text;

public delegate void DelegateZeroGroups();
public delegate void DelegateMoreThanFiveStudentsInGroup(String^ group, int GroupSize);

int CafedraSIZE = 0;

ref class Student
{
public:
    String^ StudentName;
    int number;
    void SetStudent()
    {
        Console::WriteLine("Enter student's name:");
        StudentName = Convert::ToString(Console::ReadLine());
    }
};

template <class T>
ref class Group
{
public:
    event DelegateZeroGroups^ ZeroGroups;
    event DelegateMoreThanFiveStudentsInGroup^ MoreFiveStudents;
    String^ GroupName;
    array < T^ >^ Students;
    int size;
    Group()
    {
        Console::WriteLine("Enter group name:");
        GroupName = Convert::ToString(Console::ReadLine());
        size = 0;
        Students = gcnew array < T^ >(size);
    }
    void AddNewStudent()
    {
        size += 1;
        array< T^ >^ temp = gcnew array < T^ >(size);
        for (int i = 0; i < size; i++)
        {
            if (i == size - 1)
            {
                temp[size - 1] = gcnew T;
                temp[size - 1]->number = (size - 1);
                temp[size - 1]->SetStudent();
            }
            else
            {
                temp[i] = gcnew T;
                temp[i] = Students[i];
            }
        }
        delete Students;
        Students = gcnew array < T^ >(size);
        for (int i = 0; i < size; i++)
        {
            Students[i] = gcnew T;
            Students[i] = temp[i];
        }
        delete temp;
        Cafedra();

        if (size > 5)
        {
            Student(GroupName, size);
        }
    }
    void DeleteStudent(int number)
    {
        size -= 1;
        array< T^ >^ temp = gcnew array < T^ >(size);
        for (int i = 0; i < size; i++)
        {
            if (i < number)
            {
                temp[i] = gcnew T;
                temp[i] = Students[i];
            }
            else if (i > number)
            {
                temp[i] = gcnew T;
                temp[i] = Students[i];
                Students[i]->number -= 1;
            }
            else if (number + 1 == size)
            {
                temp[i] = gcnew T;
                temp[i] = Students[i + 1];
                Students[i + 1]->number -= 1;
            }
        }
        delete Students;
        Students = gcnew array < T^ >(size);
        for (int i = 0; i < size; i++)
        {
            Students[i] = gcnew T;
            Students[i] = temp[i];
        }
        delete temp;
        Cafedra();
    }
    void GetGroup()
    {
        for (int i = 0; i < size; i++)
        {
            Console::WriteLine("Group name:\t" + GroupName + "\nID:\t" + Students[i]->number + "\nStudent's name:\t" + Students[i]->StudentName);
        }
    }
};

template <class T>
ref class CAFEDRA
{
public:
    event DelegateZeroGroups^ ZeroGroups;
    event DelegateMoreThanFiveStudentsInGroup^ MoreFiveStudents;
    String^ GroupName;
    array < T^ >^ Students;
    int size;
    CAFEDRA()
    {
        Console::WriteLine("Enter group name:");
        GroupName = Convert::ToString(Console::ReadLine());
        size = 0;
        Groups = gcnew array < T^ >(size);
    }
    void AddNewGroup()
    {
        size += 1;
        array< T^>^ temp = gcnew array < T^> >(size);
        for (int i = 0; i < size; i++)
        {
            if (i == size - 1)
            {
                temp[size - 1] = gcnew T;
                temp[size - 1]->number = (size - 1);
                temp[size - 1]->Group();
            }
            else
            {
                temp[i] = gcnew T;
                temp[i] = Groups[i];
            }
        }
        delete Groups;
        Groups = gcnew array < T^ >(size);
        for (int i = 0; i < size; i++)
        {
            Groups[i] = gcnew T;
            Groups[i] = temp[i];
        }
        delete temp;
        Cafedra();

        if (size > 5) //Условие выполнения пункта 2)
        {
            MoreFiveStudents(GroupName, size);
        }
    }
    void DeleteGroup(int id)
    {
        size -= 1;
        array< T^ >^ temp = gcnew array < T^ >(size);
        for (int i = 0; i < size; i++)
        {
            if (i < id)
            {
                temp[i] = gcnew T;
                temp[i] = Groups[i];
            }
            else if (i > id)
            {
                temp[i] = gcnew T;
                temp[i] = Groups[i];
                Groups[i]->id -= 1;
            }
            else if (number + 1 == size)
            {
                temp[i] = gcnew T;
                temp[i] = Groups[i + 1];
                Groups[i + 1]->id -= 1;
            }
        }
        delete Groups;
        Groups = gcnew array < T^ >(size);
        for (int i = 0; i < size; i++)
        {
            Groups[i] = gcnew T;
            Groups[i] = temp[i];
        }
        delete temp;
        if (size == 0)
            ZeroGroups();
    }
};

ref class Events
{
public:
    void FiveStudentsMethod(String^ GroupName, int size)
    {
        Console::WriteLine("Students in group " + GroupName + " > 5. Total in that group " + size + " students\n");
        Console::ReadKey();
    }
    void ZeroGroupsMethod()
    {
        Console::WriteLine("There are 0 students at the cafedra");
        Console::ReadKey();
    }
};

ref class Report
{
public:
    Report()
    {
        File::WriteAllText("Report.txt", "Event report\n");
    }
    void FiveStudentsMethod(String^ GroupName, int size)
    {
        String^ Message = "Students in group " + GroupName + " > 5. Total in that group " + size + " students\n";
        File::AppendAllText("Report.txt", Message);
    }
    void ZeroGroupsMethod()
    {
        String^ Message = "There are 0 students at the cafedra";
        File::AppendAllText("Report.txt", Message);
    }
};

int main()
{
    int amount, menu;
    Console::OutputEncoding = Encoding::UTF8;

    Console::WriteLine("Enter number of groups at the cafedra:");
    amount = Convert::ToInt32(Console::ReadLine());

    CAFEDRA<array<Group<Student>^>>^ CAF = gcnew CAFEDRA<array<Group<Student>^>>;

    for (int i = 0; i < amount; i++)
    {
        CAF[i] = gcnew CAFEDRA<array<Group<Student>^>>;
    }

    Events^ Event = gcnew Events();
    Report^ txt = gcnew Report();

    for (int i = 0; i < amount; i++)
    {
        CAF[i]->ZeroGroups += gcnew DelegateZeroGroups(Event, &Events::ZeroGroupsMethod);
        CAF[i]->ZeroGroups += gcnew DelegateZeroGroups(txt, &Report::ZeroGroupsMethod);
        CAF[i]->FiveStudents += gcnew DelegateMoreThanFiveStudentsInGroup(Event, &Events::FiveStudentsMethod);
        CAF[i]->FiveStudents += gcnew DelegateMoreThanFiveStudentsInGroup(txt, &Report::FiveStudentsMethod);
    }

    while (true)
    {
        for (int i = 0; i < amount; i++)
        {
            CAF[i]->GetGroup();
        }
        Console::WriteLine("1. Add a student \n2. Delete student\n3. Add group\n4. Delete group");
        menu = Convert::ToInt32(Console::ReadLine());
        switch (menu)
        {
        case 1:
        {
            String^ name;
            Console::WriteLine("Enter group name: ");
            name = Convert::ToString(Console::ReadLine());
            for (int i = 0; i < amount; i++)
            {
                if (CAF[i]->GroupName == name)
                {
                    CAF[i]->AddNewStudent();
                }
            }
            break;
        }
        case 2:
        {
            String^ name;
            Console::WriteLine("Enter group name: ");
            name = Convert::ToString(Console::ReadLine());
            for (int i = 0; i < amount; i++)
            {
                if (CAF[i]->GroupName == name)
                {
                    int id;
                    Console::WriteLine("Enter student id: ");
                    id = Convert::ToInt32(Console::ReadLine());
                    CAF[i]->DeleteStudent(id);
                }
            }
            break;
        }
        case 3:
            String ^ name;
            Console::WriteLine("Enter group name: ");
            name = Convert::ToString(Console::ReadLine());
            for (int i = 0; i < amount; i++)
            {
                String^ name;
                name = Convert::ToString(Console::ReadLine());
                CAF[i]->AddNewGroup(name);
            }
            break;
        
        case 4:
            int id;
            Console::WriteLine("Enter group name: ");
            id = Convert::ToUInt32(Console::ReadLine());
            for (int i = 0; i < amount; i++)
            {
                if (CAF[i]->GroupName == name)
                {
                    String^ name;
                    Console::WriteLine("Enter student id: ");
                    name = Convert::ToString(Console::ReadLine());
                    CAF[i]->DeleteGroup(id);
                }
            }
            break;

        default:
            Console::WriteLine("Wrong choice!");
            break;
        }
    }
}
