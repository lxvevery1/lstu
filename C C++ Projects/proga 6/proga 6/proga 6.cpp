#include <iostream>
#include <fstream>
#include <boost\archive\xml_iarchive.hpp>
#include <boost\archive\xml_oarchive.hpp>
#include <boost\serialization\vector.hpp>

using namespace std;

class Furniture
{
protected:
	double length = NULL;
	double width = NULL;
	double height = NULL;
	string material = "";
};

class Legs
{
protected:
	int count;
};

class Table : public Legs, public Furniture 
{
public:
	string manufacturer; 
};

class FurnitureData : public Table
{
private:
	int id; 
public:
	FurnitureData() { }
	FurnitureData(double _length, double _width, double _height, string _material, int _count, string _manufacturer) 
	{
		length = _length;
		width = _width;
		height = _height;
		material = _material;
		count = _count;
		manufacturer = _manufacturer;
	}
	void SetId(int _id)
	{
		id = _id;
	}
	int GetId()
	{
		return id;
	}
	void Print()
	{
		cout << "Table number " << id << "\nManufacturer: " << manufacturer << "\nLength: " << length << ", Width: " << width << ", Height: " << height << ", Material: " << material << "\nNumber of legs: " << count << "\n\n";
	}
	template<class Archive> 
	void Serialize(Archive& archive, const int)
	{
		archive& BOOST_SERIALIZATION_NVP(id);
		archive& BOOST_SERIALIZATION_NVP(length);
		archive& BOOST_SERIALIZATION_NVP(width);
		archive& BOOST_SERIALIZATION_NVP(height);
		archive& BOOST_SERIALIZATION_NVP(material);
		archive& BOOST_SERIALIZATION_NVP(count);
		archive& BOOST_SERIALIZATION_NVP(manufacturer);
	}
};

class Base
{
private:
	unsigned int noHeader = boost::archive::no_header;
	int idNum = 1;
	vector<FurnitureData> tables = {};
public:
	template<class Archive> void Serialize(Archive& archive, const int) 
	{
		archive& BOOST_SERIALIZATION_NVP(idNum);
		archive& BOOST_SERIALIZATION_NVP(tables);
	}
	void LoadFromFile() 
	{
		Base base;
		ifstream inputStream("Furniture.xml", ios::binary);
		boost::archive::xml_iarchive inputArchive(inputStream, noHeader);
		inputArchive >> BOOST_SERIALIZATION_NVP(base);
		SetTables(base.GetTables());
		inputStream.close();
	}
	void UploadToFile() 
	{
		ofstream outputStream("Furniture.xml", ios::binary);
		boost::archive::xml_oarchive outputArchive(outputStream, noHeader);
		Base newbase = *this;
		outputArchive << BOOST_SERIALIZATION_NVP(newbase);
		outputStream.close();
	}
	void SetTables(vector<FurnitureData> _tables)
	{
		tables = _tables;
	}
	vector<FurnitureData> GetTables()
	{
		return tables;
	}
	void Print() 
	{
		cout << "Tables: \n";
		for (size_t i = 0; i < tables.size(); i++) {
			tables[i].Print();
		}
		if (tables.empty()) cout << "Tables list is empty!\n";
	}
	void AddTable() 
	{
		double length, width, height;
		string material, manufacturer;
		int count;
		cout << "Input manufacturer: ";
		cin >> manufacturer;
		cout << "Input specifications (lenght, width, height): ";
		cin >> length >> width >> height;
		cout << "Input material: ";
		cin >> material;
		cout << "Input number of legs: ";
		cin >> count;
		FurnitureData data = FurnitureData(length, width, height, material, count, manufacturer);
		data.SetId(idNum);
		idNum++;
		tables.push_back(data);
		cout << "Table added.\n";
		data.Print();
	}
	void DeleteById(int _id) 
	{
		int id = SearchById(_id);
		if (id == 0) cout << "Current id doesn't exists\n";
		else {
			tables.erase(tables.begin() + id);
			cout << "Table removed\n";
		}
	}
	void EditById(int id, FurnitureData table) 
	{
		tables[SearchById(id)] = table;
	}
	int SearchById(int _id)
	{
		for (size_t i = 0; i < tables.size(); i++) {
			if (tables[i].GetId() == _id) return i;
		}
		return 0;
	}
	bool isEmpty() 
	{
		if (tables.empty())
			return true;
		else
			return false;
	}
};

int main()
{
	int choice, id, count;
	double length, width, height;
	string material, manufacturer;
	Base base;
	FurnitureData data;
	do
	{
		cout << "1. Add table" << endl << "2. Delete table" << endl << "3. Change specifications" << endl << "4. Upload data in file" << endl << "5. Load data from file" << endl << "6. Table output" << endl << "0. Exit" << endl;
		cin >> choice;
		switch (choice)
		{
		case 1:
			base.AddTable();
			break;
		case 2:
			cout << "Input table-id, which want to delete\n";
			cin >> id;
			base.DeleteById(id);
			break;
		case 3:
			cout << "Input table-id, which want to change\n";
			cin >> id;
			base.SearchById(id);
			if (id == -1)
			{
				cout << "This id doesn't exist\n";
				break;
			}
			cout << "Input manufacturer: ";
			cin >> manufacturer;
			cout << "Input specifications (lenght, width, height): ";
			cin >> length >> width >> height;
			cout << "Input material: ";
			cin >> material;
			cout << "Input nomber of legs: ";
			cin >> count;
			data = FurnitureData(length, width, height, material, count, manufacturer);
			data.SetId(id);
			base.EditById(id, data);
		case 4:
			if (base.isEmpty())
			{
				cout << "There empty list" << endl;
				break;
			}
			base.UploadToFile();
			cout << "Data uploaded\n";
			break;
		case 5:
			base.LoadFromFile();
			base.Print();
			break;
		case 6:
			base.Print();
			break;
		}
	} while (choice != 0);
	return 0;
}
