<link rel="stylesheet" href="https://cdn.jsdelivr.net/npm/water.css@2/out/water.css">
<?php
if ($_SERVER["REQUEST_METHOD"] === "POST") {
    $name = $_POST["name"];
    $email = $_POST["email"];
    $rating = $_POST["rating"];
    $review = $_POST["review"];
    $photo = $_FILES["photo"];

    // Валидация имени (только буквы и дефисы, не менее 2 символов)
    if (!preg_match("/^[A-Za-z-]{2,}$/", $name)) {
        echo "Ошибка: Неверный формат имени.";
        exit;
    }

    // Валидация email
    if (!filter_var($email, FILTER_VALIDATE_EMAIL)) {
        echo "Ошибка: Неверный формат email.";
        exit;
    }

    // Проверка и обработка фотографии
    $upload_directory = "uploads/";
    $file_extension = pathinfo($photo["name"], PATHINFO_EXTENSION);
    $allowed_extensions = ["jpg", "jpeg", "png"];

    if (!in_array(strtolower($file_extension), $allowed_extensions)) {
        echo "Ошибка: Недопустимый формат файла. Разрешены только JPG, JPEG и PNG.";
        exit;
    }

    $unique_filename = uniqid() . "." . $file_extension;
    $photo_path = $upload_directory . $unique_filename;

    if (move_uploaded_file($photo["tmp_name"], $photo_path)) {
        // Подключение к базе данных PostgreSQL
        $pdo = new PDO("pgsql:host=localhost;dbname=my_reviews_db", "postgres", "");
    
        // Подготовка и выполнение SQL-запроса для вставки данных
        $stmt = $pdo->prepare("INSERT INTO reviews (email, name, date_insert, rate, text, image_path) VALUES (?, ?, NOW(), ?, ?, ?)");
        $stmt->execute([$email, $name, $rating, $review, $photo_path]);

        echo "Отзыв успешно отправлен и сохранен в базе данных.";

        $stmt = $pdo->query("SELECT email, name, date_insert, rate, text, image_path FROM reviews");
        
        while ($row = $stmt->fetch(\PDO::FETCH_ASSOC)) {
            $stocks[] = [
                'email' => $row['email'],
                'name' => $row['name'],
                'date_insert' => $row['date_insert'],
                'rate' => $row['rate'],
                'text' => $row['text'],
                'image_path' => $row['image_path'],
            ];
        }
        ?>
        <!DOCTYPE html>
<html>
    <head>
        <title>Список отзывов PostgreSQL</title>
    </head>
    <body>
        <div class="container">
            <h1>Список отзывов</h1>
            <table class="table table-bordered">
                <thead>
                    <tr>
                        <th>Почта</th>
                        <th>Имя</th>
                        <th>Дата</th>
                        <th>Оценка</th>
                        <th>Текст</th>
                        <th>Путь до изображения</th>
                    </tr>
                </thead>
                <tbody>
                    <?php foreach ($stocks as $stock) : ?>
                        <tr>
                            <td><?php echo ($stock['email']) ?></td>
                            <td><?php echo ($stock['name']); ?></td>
                            <td><?php echo ($stock['date_insert']); ?></td>
                            <td><?php echo ($stock['rate']); ?></td>
                            <td><?php echo ($stock['text']); ?></td>
                            <td><?php echo ($stock['image_path']); ?></td>
                        </tr>
                    <?php endforeach; ?>
                </tbody>
            </table>
        </div>
    </body>
</html>
<?php
    } else {
        echo "Ошибка при загрузке фото.";
    }
} else {
    echo "Доступ запрещен.";
}
?>