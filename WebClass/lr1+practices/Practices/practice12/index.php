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
        // Перенаправление на index.php после успешной аутентификации
        header("Location: index.php");
        exit();
    } else {
        echo "Неверное имя пользователя или пароль.";
        var_dump($stmt->errorInfo());
    }
}

if (isset($_SESSION["user"])) {
    // Если пользователь аутентифицирован, показываем email и кнопку выхода
    echo "Email: " . $_SESSION["user"]["email"];
    echo "<br><a href='logout.php'>Выход</a>";

    // Добавьте форму для отправки отзыва
    echo '<h2>Оставьте отзыв</h2>';
    echo '<form action="submit_review_to_bd.php" method="post" enctype="multipart/form-data">';
    echo '    <label for="name">Имя:</label>';
    echo '    <input type="text" name="name" required><br>';
    echo '    <label for="email">Email:</label>';
    echo '    <input type="email" name="email" value="' . $_SESSION["user"]["email"] . '" required readonly><br>';
    echo '    <label for="rating">Оценка:</label>';
    echo '    <select name="rating">';
    echo '        <option value="1">1</option>';
    echo '        <option value="2">2</option>';
    echo '        <option value="3">3</option>';
    echo '        <option value="4">4</option>';
    echo '        <option value="5">5</option>';
    echo '    </select><br>';
    echo '    <label for="review">Отзыв:</label>';
    echo '    <textarea name="review" required></textarea><br>';
    echo '    <label for="photo">Фото (только .png, .jpg, .jpeg):</label>';
    echo '    <input type="file" name="photo" accept=".png, .jpg, .jpeg"><br>';
    echo '    <input type="submit" value="Отправить">';
    echo '</form>';
} else {
    header("Location: login.php");
}
?>
