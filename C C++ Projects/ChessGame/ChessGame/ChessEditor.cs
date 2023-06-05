using System;
using System.IO;
using System.Drawing;
using System.Windows.Forms;

namespace ChessForms
{
    public partial class Chess : Form
    {
        public Image chessSprites;
        public Button prevPressedButton;
        private bool isMovingMap = false;
        private bool isDeleting = false;
        private bool isMovingEditor = false;
        public int[,] map = new int[8, 8] // основная карта расположения фигур
        {
            {15, 14, 13, 12, 11, 13, 14, 15 },
            {16, 16, 16, 16, 16, 16, 16, 16 },
            {0, 0, 0, 0, 0, 0, 0, 0 },
            {0, 0, 0, 0, 0, 0, 0, 0 },
            {0, 0, 0, 0, 0, 0, 0, 0 },
            {0, 0, 0, 0, 0, 0, 0, 0 },
            {26, 26, 26, 26, 26, 26, 26, 26 },
            {25, 24, 23, 22, 21, 23, 24, 25 }
        };
        int[,] editorMap = new int[2, 6]
        {
            {16, 15, 14, 13, 12, 11 },
            {26, 25, 24, 23, 22, 21 }
        };
        public Chess()
        {
            InitializeComponent();

            chessSprites = new Bitmap("C:\\Users\\lxve_every1\\source\\repos\\ChessGame\\ChessGame\\sprites\\chess2.png"); // Наша картинка со спрайтами
            Image piece = new Bitmap(50, 50); // размер картинки
            Graphics G = Graphics.FromImage(piece); // создаем графику из картинки
            G.DrawImage(chessSprites, new Rectangle(0, 0, 50, 50), 0, 0, 150, 150, GraphicsUnit.Pixel);
            Text = "Chess Board Editor";

            Init();
        }
        void Init()
        {
            map = new int[8, 8] // карта расположения фигур
            {
            {15, 14, 13, 12, 11, 13, 14, 15 },
            {16, 16, 16, 16, 16, 16, 16, 16 },
            {0, 0, 0, 0, 0, 0, 0, 0 },
            {0, 0, 0, 0, 0, 0, 0, 0 },
            {0, 0, 0, 0, 0, 0, 0, 0 },
            {0, 0, 0, 0, 0, 0, 0, 0 },
            {26, 26, 26, 26, 26, 26, 26, 26 },
            {25, 24, 23, 22, 21, 23, 24, 25 }
            };
            CreateDefaultMap();
            CreateEditorMap();
            CreateSideButtons();
        }

        void CreateDefaultMap()
        {
            for (int i = 0; i < 8; i++)
            {
                for (int j = 0; j < 8; j++)
                {
                    Button button = new Button
                    {
                        Size = new Size(50, 50), // ее размер
                        Location = new Point(50 * j, 50 * i + 20) // ее позиция
                    }; // создаем новую кнопку для каждой фигуры


                    switch (map[i, j] / 10)
                    {
                        case 1: // для белых
                            Image piece1 = new Bitmap(50, 50); // размер одной фигуры в файле
                            Graphics G1 = Graphics.FromImage(piece1); // создаем графику из картинки
                            G1.DrawImage(chessSprites, new Rectangle(0, 0, 50, 50), 0 + 150 * (map[i, j] % 10 - 1) /*это мы вырезаем*/, 0, 150, 150, GraphicsUnit.Pixel);
                            button.BackgroundImage = piece1;
                            break;
                        case 2: // Для черных
                            Image piece2 = new Bitmap(50, 50); // размер одной фигуры в файле
                            Graphics G2 = Graphics.FromImage(piece2); // создаем графику из картинки
                            G2.DrawImage(chessSprites, new Rectangle(0, 0, 50, 50), 0 + 150 * (map[i, j] % 10 - 1) /*смещение фигур в спрайты.png*/, 150 /*настолько мы смещаемся по оси ординат*/, 150, 150, GraphicsUnit.Pixel);
                            button.BackgroundImage = piece2;
                            break;
                    }
                    button.Click += new EventHandler(OnMapFigurePress); // привязываем каждой кнопке обработчик событий с функцией
                    this.Controls.Add(button);
                }
            }
        }
        void CreateEditorMap()
        {
            for (int i = 0; i < 2; i++)
            {
                for (int j = 0; j < 6; j++)
                {
                    Button editorbutton = new Button();
                    editorbutton.Size = new Size(50, 50);
                    editorbutton.Location = new Point(j * 50 + 50, i * 50 + 410);

                    switch (editorMap[i, j] / 10)
                    {
                        case 1:
                            Image piece1 = new Bitmap(50, 50);
                            Graphics G1 = Graphics.FromImage(piece1);
                            G1.DrawImage(chessSprites, new Rectangle(0, 0, 50, 50), 0 + 150 * (editorMap[i, j] % 10 - 1), 0, 150, 150, GraphicsUnit.Pixel);
                            editorbutton.BackgroundImage = piece1;
                            break;
                    }
                    switch (editorMap[i, j] / 10)
                    {
                        case 2:
                            Image piece1 = new Bitmap(50, 50);
                            Graphics G1 = Graphics.FromImage(piece1);
                            G1.DrawImage(chessSprites, new Rectangle(0, 0, 50, 50), 0 + 150 * (editorMap[i, j] % 10 - 1), 150, 150, 150, GraphicsUnit.Pixel);
                            editorbutton.BackgroundImage = piece1;
                            break;
                    }
                    editorbutton.Click += new EventHandler(OnEditorFigurePress); // привязываем каждой кнопке обработчик событий с функцией
                    this.Controls.Add(editorbutton); // применяет наши кнопки
                }
            }
        }
        void CreateSideButtons()
        {
            Button Refresh = new Button();
            Button Delete = new Button();
            

            Refresh.Location = new Point(436, 115);
            Delete.Location = new Point(436, 76);

            Refresh.Size = new Size(75, 23);
            Delete.Size = new Size(75, 23);

            Refresh.Text = "Обновить";
            Delete.Text = "Удалить";
            

            Refresh.Click += new EventHandler(Refresh_Click);
            Delete.Click += new EventHandler(Delete_Click);

            Controls.Add(Refresh);
            Controls.Add(Delete);
        }
        void CreateToolStripMenuItems()
        {
            ToolStripMenuItem File = new ToolStripMenuItem();
            ToolStripMenuItem Load = new ToolStripMenuItem();
            ToolStripMenuItem Save = new ToolStripMenuItem();

            File.Size = new Size(48, 20);
            Load.Size = new Size(180, 22);
            Save.Size = new Size(180, 22);

            File.Text = "Файл";
            Load.Text = "Загрузить";
            Save.Text = "Сохранить";

            File.Click += new EventHandler(файлToolStripMenuItem_Click);
            Load.Click += new EventHandler(загрузитьToolStripMenuItem_Click);
            Save.Click += new EventHandler(сохранитьToolStripMenuItem_Click);

            File.DropDownItems.Add(Load);
            File.DropDownItems.Add(Save);

            this.menuStrip1.Items.Add(File);
        }
        void OnMapFigurePress(object sender, EventArgs e)
        {
            if (prevPressedButton != null)
                prevPressedButton.BackColor = Color.AntiqueWhite;

            Button pressedButton = sender as Button;

            if (map[pressedButton.Location.Y / 50, pressedButton.Location.X / 50] != 0 && !isDeleting) // чтобы пустое место не выделялось
            {
                pressedButton.BackColor = Color.SandyBrown;
                isMovingMap = true;
                isMovingEditor = false;
            }
            else
            {
                if (isMovingEditor)
                {
                    isMovingMap = isDeleting = false;
                    map[pressedButton.Location.Y / 50, pressedButton.Location.X / 50] = editorMap[(prevPressedButton.Location.Y - 410) / 50, (prevPressedButton.Location.X - 50) / 50];
                    pressedButton.BackgroundImage = prevPressedButton.BackgroundImage;
                    isMovingEditor = false;
                }
                if (isMovingMap)
                {
                    isMovingEditor = isDeleting = false;
                    map[pressedButton.Location.Y / 50, pressedButton.Location.X / 50] = map[(prevPressedButton.Location.Y) / 50, (prevPressedButton.Location.X) / 50]; // меняем значение новой ячейки в массиве на значение старой ячейки
                    map[prevPressedButton.Location.Y / 50, prevPressedButton.Location.X / 50] = 0; // меняем значение старой ячейки на сохраненную
                    pressedButton.BackgroundImage = prevPressedButton.BackgroundImage; // устанавливаем старую картинку новой ячейке
                    prevPressedButton.BackgroundImage = null; // убираем картинку на старой ячейке
                    isMovingMap = false;
                }
                if (isDeleting)
                {
                    isMovingEditor = isMovingMap = false;
                    map[pressedButton.Location.Y / 50, pressedButton.Location.X / 50] = 0;
                    pressedButton.BackgroundImage = null;
                    isDeleting = false;
                }
            }
            prevPressedButton = pressedButton;
        }
        void OnEditorFigurePress(object sender, EventArgs e)
        {
            if (prevPressedButton != null)
                prevPressedButton.BackColor = Color.White;

            Button pressedButton = sender as Button;

            if (editorMap[(pressedButton.Location.Y - 410) / 50, (pressedButton.Location.X - 50) / 50] != 0) // чтобы пустое место не выделялось
            {
                pressedButton.BackColor = Color.Wheat;
                isMovingEditor = true;
                isMovingMap = false;
                isDeleting = false;
            }
            prevPressedButton = pressedButton;
        }

        void Delete_Click(object sender, EventArgs e)
        {
            Button pressedButton = sender as Button;

            if (pressedButton.Location.X == 436 && pressedButton.Location.Y == 76) // чтобы пустое место не выделялось
            {
                pressedButton.BackColor = Color.Red;
                isDeleting = true;
                isMovingMap = false;
                isMovingEditor = false;
            }
            prevPressedButton = pressedButton;
        }
        void Refresh_Click(object sender, EventArgs e)
        {
            for (int i = this.Controls.Count - 1; i >= 0; i--)
            {
                if (this.Controls[i].GetType() != typeof(MenuStrip))
                {
                    this.Controls[i].Dispose();
                }
            }
            Init();
        }
        void загрузитьToolStripMenuItem_Click(object sender, EventArgs e)
        {
            string path = @"C:\Users\lxve_every1\Desktop\ser\savemap.txt";

            string[] lines = File.ReadAllLines(path);
            int[,] loadmap = new int[8, 8];

            for (int i = 0; i < map.GetLength(0); i++)
            {
                string[] tokens = lines[i].Split();
                for (int j = 0; j < map.GetLength(1); j++)
                {
                    loadmap[i, j] = int.Parse(tokens[j]);
                }
            }
            map = loadmap;

            for (int i = this.Controls.Count - 1; i >= 0; i--)
            {
                if (this.Controls[i].GetType() != typeof(MenuStrip))
                {
                    this.Controls[i].Dispose();
                }
            }

            CreateDefaultMap();
            CreateEditorMap();
            CreateSideButtons();
        }
        void сохранитьToolStripMenuItem_Click(object sender, EventArgs e)
        {
            int[,] savemap = map;
            string path = @"C:\Users\lxve_every1\Desktop\ser\savemap.txt";

            using (StreamWriter SW = new StreamWriter(path))
            {
                for (int i = 0; i < 8; i++)
                {
                    for (int j = 0; j < 8; j++)
                    {
                        SW.Write(savemap[i,j] + " ");
                    }
                    SW.WriteLine("");
                }
                SW.Close();
            }
        }
        void файлToolStripMenuItem_Click(object sender, EventArgs e)
        {

        }

        void Form1_Load(object sender, EventArgs e) { }

    }
}
