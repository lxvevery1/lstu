<?php
// Подключение к базе данных
$mysqli = new mysqli("localhost", "root", "", "authentificationdb");

// Проверка подключения к базе данных
if ($mysqli->connect_errno) {
    die("Error: " . $mysqli->connect_error);
}

// Функция проверки аутентификации пользователя
function isUserAuthenticated() {
    return isset($_SESSION["id"]);
}

// Функция проверки, является ли пользователь администратором
function isUserAdmin() {
    global $mysqli;

    if (isUserAuthenticated()) {
        $userId = $_SESSION["id"];
        $query = "SELECT admin FROM user WHERE id = '$userId'";

        if ($result = $mysqli->query($query)) {
            $row = $result->fetch_assoc();
            $admin = $row["admin"];

            // Проверка, является ли пользователь администратором
            return $admin == 1;
        }
    }

    return false;
}

if (!isUserAuthenticated()){
    header("Location: http://localhost/dbKeywords/Authentification/index.php");
    exit;
}

?>