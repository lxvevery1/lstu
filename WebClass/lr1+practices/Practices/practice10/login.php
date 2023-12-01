<link rel="stylesheet" href="https://cdn.jsdelivr.net/npm/water.css@2/out/water.css">
<?php
session_start();

if ($_SERVER["REQUEST_METHOD"] === "POST") {
    $username = $_POST["username"];
    $password = $_POST["password"];

    // Подключение к базе данных для проверки логина и пароля
    $pdo = new PDO("pgsql:host=localhost;dbname=my_reviews_db", "postgres", "");
    $stmt = $pdo->prepare("SELECT * FROM users WHERE name = ? AND password = ?");
    $stmt->execute([$username, hash('sha256', $password)]);
    $user = $stmt->fetch();

    if ($user) {
        // Успешная аутентификация
        $_SESSION["user"] = $user;
    } else {
        echo "Неверное имя пользователя или пароль.";
    }
}

if (isset($_SESSION["user"])) {
    // Если пользователь аутентифицирован, показываем email и кнопку выхода
    echo "Email: " . $_SESSION["user"]["email"];
    echo "<br><a href='logout.php'>Выход</a>";
    echo "<br><br>
    <a href='index.php'>Перейти к форме отзыва</a>";
} else {
    // Показываем форму входа
    echo '<form method="post" action="login.php">
            <label for="username">Имя пользователя:</label>
            <input type="text" name="username" required><br>
            <label for="password">Пароль:</label>
            <input type="password" name="password" required><br>
            <input type="submit" value="Войти">
        </form>';
}
?>