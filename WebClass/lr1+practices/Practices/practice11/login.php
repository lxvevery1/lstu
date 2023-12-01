<?php
session_start();

// Подключение к базе данных
$pdo = new PDO("pgsql:host=localhost;dbname=my_reviews_db", "postgres", "");

if ($_SERVER["REQUEST_METHOD"] === "POST") {
    if (isset($_POST["username"])) {
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
        }
    } elseif (isset($_POST["register"])) {
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
            // Проверка уникальности логина и email
            $stmtLogin = $pdo->prepare("SELECT * FROM users WHERE login = ?");
            $stmtLogin->execute([$login]);
            $userLogin = $stmtLogin->fetch();

            $stmtEmail = $pdo->prepare("SELECT * FROM users WHERE email = ?");
            $stmtEmail->execute([$email]);
            $userEmail = $stmtEmail->fetch();

            if ($userLogin) {
                echo "Пользователь с таким логином уже существует.";
            } elseif ($userEmail) {
                echo "Пользователь с таким email уже существует.";
            } else {
                // Хеширование пароля
                $hashedPassword = hash('sha256', $password);

                // Вставка данных в таблицу users
                $stmtInsert = $pdo->prepare("INSERT INTO users (login, email, phone, password) VALUES (?, ?, ?, ?)");
                $stmtInsert->execute([$login, $email, $phone, $hashedPassword]);

                echo "Регистрация успешна. Теперь вы можете войти в систему.";
            }
        }
    }
}
?>

<!-- HTTP -->


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

        .form-container {
            display: flex;
            flex-direction: column;
            align-items: center;
        }

        .form-container form {
            display: none;
            width: 300px;
            margin-top: 20px;
        }

        .form-container form.active {
            display: block;
        }
    </style>
</head>
<body>
    <h1>Вход и регистрация</h1>

    <div class="tabs">
        <div class="tab active" onclick="showForm('loginForm', this)">Вход</div>
        <div class="tab" onclick="showForm('registerForm', this)">Регистрация</div>
    </div>

    <div class="form-container">
        <!-- Форма авторизации -->
        <form id="loginForm" class="active" method="post" action="login.php">
            <label for="username">Имя пользователя:</label>
            <input type="text" name="username" required><br>
            <label for="password">Пароль:</label>
            <input type="password" name="password" required><br>
            <input type="submit" value="Войти">
        </form>

        <!-- Форма регистрации -->
        <form id="registerForm" method="post" action="login.php">
            <label for="login">Логин:</label>
            <input type="text" name="login" required><br>
            <label for="email">Email:</label>
            <input type="email" name="email" required><br>
            <label for="phone">Телефон:</label>
            <input type="text" name="phone" required><br>
            <label for="password">Пароль:</label>
            <input type="password" name="password" required><br>
            <label for="confirm_password">Повторите пароль:</label>
            <input type="password" name="confirm_password" required><br>
            <input type="checkbox" name="consent" required> Согласие на обработку персональных данных<br>
            <input type="submit" name="register" value="Зарегистрироваться">
        </form>
    </div>

    <script>
        function showForm(formId, clickedTab) {
            const tabs = document.querySelectorAll('.tab');
            tabs.forEach(tab => tab.classList.remove('active'));
            clickedTab.classList.add('active');

            const forms = document.querySelectorAll('.form-container form');
            forms.forEach(form => form.classList.remove('active'));

            const activeForm = document.getElementById(formId);
            activeForm.classList.add('active');
        }
    </script>
</body>
</html>