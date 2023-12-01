<link rel="stylesheet" href="https://cdn.jsdelivr.net/npm/water.css@2/out/water.css">
<?php
$host = "localhost";
$dbname = "postgres";
$user = "postgres";
$pass = "";

try {
    $pdo = new PDO("pgsql:host=$host;dbname=$dbname", $user, $pass);
    $pdo->setAttribute(PDO::ATTR_ERRMODE, PDO::ERRMODE_EXCEPTION);

    $sql = "SELECT * FROM mytable";
    $stmt = $pdo->query($sql);

    echo "<table>";
    echo "<tr><th>ID</th><th>Name</th><th>Age</th></tr>";

    while ($row = $stmt->fetch(PDO::FETCH_ASSOC)) {
        echo "<tr><td>{$row['id']}</td><td>{$row['name']}</td><td>{$row['age']}</td></tr>";
    }

    echo "</table>";
} catch (PDOException $e) {
    echo "Ошибка: " . $e->getMessage();
}
?>
