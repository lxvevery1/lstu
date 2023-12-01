<?php
session_start();

// Подключение к базе данных
$pdo = new PDO("pgsql:host=localhost;dbname=my_reviews_db", "postgres", "");

if ($_SERVER["REQUEST_METHOD"] === "POST") {
    if (isset($_POST["action"])) {
        // Обработка формы
        $action = $_POST["action"];

        if ($action === "login") {
            // Обработка формы входа
            $login = $_POST["username"];
            $password = $_POST["password"];

            // Проверка логина и пароля в базе данных
            $stmt = $pdo->prepare("SELECT * FROM users WHERE login = ? AND password = ?");
            $stmt->execute([$login, hash('sha256', $password)]);
            $user = $stmt->fetch();

            if ($user) {
                // Успешная аутентификация
                $_SESSION["user"] = $user;
                header("Location: index.php");
                exit();
            } else {
                echo "Неверное имя пользователя или пароль.";
                exit();
            }
        } elseif ($action === "register") {
            // Обработка формы регистрации
            $login = $_POST["login"];
            $email = $_POST["email"];
            $phone = $_POST["phone"];
            $password = $_POST["password"];
            $confirmPassword = $_POST["confirm_password"];
            $consent = isset($_POST["consent"]);

            // Валидация данных (в данном примере простая валидация)
            if (empty($login) || empty($email) || empty($phone) || empty($password) || empty($confirmPassword) || !$consent) {
                echo "Заполните все поля и подтвердите согласие на обработку персональных данных.";
            } elseif ($password !== $confirmPassword) {
                echo "Пароли не совпадают.";
            } else {
                $rawPhone = preg_replace('/[^0-9]/', '', $_POST["phone"]);

                // Проверка уникальности логина и email
                $stmtLogin = $pdo->prepare("SELECT * FROM users WHERE login = ?");
                $stmtLogin->execute([$login]);
                $userLogin = $stmtLogin->fetch();

                $stmtEmail = $pdo->prepare("SELECT * FROM users WHERE email = ?");
                $stmtEmail->execute([$email]);
                $userEmail = $stmtEmail->fetch();
                
                $stmtPhone = $pdo->prepare("SELECT * FROM users WHERE phone = ?");
                $stmtPhone->execute([$rawPhone]);
                $userPhone = $stmtPhone->fetch();

                if ($userLogin) {
                    echo "Пользователь с таким логином уже существует.";
                } elseif ($userEmail) {
                    echo "Пользователь с таким email уже существует.";
                } elseif ($userPhone) {
                    echo "Пользователь с таким телефоном уже существует.";
                } else {
                    // Хеширование пароля
                    $hashedPassword = hash('sha256', $password);

                    // Вставка данных в таблицу users
                    $stmtInsert = $pdo->prepare("INSERT INTO users (login, email, phone, password) VALUES (?, ?, ?, ?)");
                    $stmtInsert->execute([$login, $email, $rawPhone, $hashedPassword]);

                    echo "Регистрация успешна. Теперь вы можете войти в систему.";
                }
            }
        }
    }
}
?>

<!-- HTTP -->
<script src="https://cdnjs.cloudflare.com/ajax/libs/jquery/3.6.0/jquery.min.js"></script>
<script src="https://cdnjs.cloudflare.com/ajax/libs/jquery.inputmask/5.0.6/jquery.inputmask.min.js"></script>

<link rel="stylesheet" href="https://cdn.jsdelivr.net/npm/water.css@2/out/water.css">
<!DOCTYPE html>
<html lang="en">
<head>
    <meta charset="UTF-8">
    <meta name="viewport" content="width=device-width, initial-scale=1.0">
    <title>Форма входа и регистрации</title>
    <style>
        .tabs {
            display: flex;
            justify-content: space-around;
            margin-bottom: 30px;
        }

        .tab {
            cursor: pointer;
            padding: 8px 20px;
            border: 2px solid #ccc;
            border-radius: 5px;
        }

        .tab.active {
            background-color: #101820;
        }

        .tab.darkened {
            background-color: #555; /* Change this to the desired darkened color */
            color: #fff; /* Change this to the desired text color */
        }

        .form-container {
            display: flex;
            flex-direction: column;
            align-items: center;
        }

        .form-popup {
            display: none;
            position: fixed;
            top: 50%;
            left: 50%;
            transform: translate(-50%, -50%);
            padding: 20px;
            background-color: #fff;
            border: 1px solid #ccc;
            border-radius: 5px;
            z-index: 1;
        }

        .form-container form {
            width: 300px;
            margin-top: 20px;
        }

        .form-container form.active {
            display: block;
        }
        
        .popup {
            display: none;
            position: fixed;
            top: 50%;
            left: 50%;
            transform: translate(-50%, -50%);
            padding: 20px;
            background-color: #fff;
            border: 1px solid #ccc;
            box-shadow: 0 2px 10px rgba(0, 0, 0, 0.1);
            z-index: 1000;
        }

        .popup.active {
            background-color: #000000;
        }

    /* (затемнение фона) */
        .overlay {
            display: none;
            position: fixed;
            top: 0;
            left: 0;
            width: 100%;
            height: 100%;
            background-color: rgba(0, 0, 0, 0.5);
            z-index: 999;
        }

        .overlay.active {
        display: block;
        }
    </style>
</head>
<body>
    <h1>Вход и регистрация</h1>

    <div class="tabs">
        <div class="tab active" onclick="showForm('loginForm')">Вход</div>
        <div class="tab" onclick="showForm('registerForm')">Регистрация</div>
    </div>

    <div id="loginFormPopup" class="form-popup">
        <!-- Форма авторизации -->
        <form id="loginForm" method="post" action="login.php">
            <input type="hidden" name="action" value="login">
            <label for="username">Имя пользователя:</label>
            <input type="text" name="username" required><br>
            <label for="password">Пароль:</label>
            <input type="password" name="password" required><br>
            <input type="submit" value="Войти">
        </form>
        <button onclick="hideForm('loginFormPopup')">Закрыть</button>
    </div>


    <div id="registerFormPopup" class="form-popup">
        <!-- Форма регистрации -->
        <form id="registerForm" method="post" action="login.php">
            <input type="hidden" name="action" value="register">
            <label for="login">Логин:</label>
            <input type="text" name="login" required><br>
            <label for="email">Email:</label>
            <input type="email" name="email" required><br>
            <label for="phone">Телефон:</label>
            <input type="text" name="phone" id="phoneInput" required><br>
            <label for="password">Пароль:</label>
            <input type="password" name="password" required><br>
            <label for="confirm_password">Повторите пароль:</label>
            <input type="password" name="confirm_password" required><br>
            <input type="checkbox" name="consent" required> Согласие на обработку персональных данных<br>
            <input type="submit" name="register" value="Зарегистрироваться">
        </form>
        <button onclick="hideForm('registerFormPopup')">Закрыть</button>
    </div>
    <script>
        function showForm(formId) {
            const formPopup = document.getElementById(formId + 'Popup');
            formPopup.style.display = 'block';

            // Darken the corresponding tab button
            const tabButton = document.querySelector(`.tab[data-form="${formId}"]`);
            tabButton.classList.add('darkened');
        }

        function hideForm(formId) {
            const formPopup = document.getElementById(formId);
            formPopup.style.display = 'none';

            // Remove the darkening from the corresponding tab button
            const tabButton = document.querySelector(`.tab[data-form="${formId}"]`);
            tabButton.classList.remove('darkened');
        }

        function showPopup(content) {
            const popup = document.querySelector('.popup');
            const overlay = document.querySelector('.overlay');
            const popupContent = document.querySelector('.popup-content');

            popupContent.innerHTML = content;
            popup.style.display = 'block';
            overlay.style.display = 'block';
        }

        function hidePopup() {
            const popup = document.querySelector('.popup');
            const overlay = document.querySelector('.overlay');

            popup.style.display = 'none';
            overlay.style.display = 'none';
        }
        $(document).ready(function() {
            // Initialize Inputmask with the desired mask
            $('#phoneInput').inputmask('+7 (999) 999-99-99');
        });
        </script>
</body>
</html>
