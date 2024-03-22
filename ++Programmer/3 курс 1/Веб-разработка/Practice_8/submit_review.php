<?php
if ($_SERVER["REQUEST_METHOD"] === "POST") {
    $name = $_POST["name"];
    $email = $_POST["email"];
    $rating = $_POST["rating"];
    $review = $_POST["review"];
    $photo = $_FILES["photo"];

    // Проверка и обработка фотографии
    $upload_directory = "uploads/";
    $photo_path = $upload_directory . $photo["name"];
    if (move_uploaded_file($photo["tmp_name"], $photo_path)) {
        // Файл успешно сохранен

        // Открыть файл reviews.txt для записи данных
        $file = fopen("reviews.txt", "a");

        if ($file) {
            $data = "Name: $name\nEmail: $email\nRating: $rating\nReview: $review\nPhoto Path: $photo_path\n\n";
            fwrite($file, $data);
            fclose($file);
            echo "Отзыв успешно отправлен и сохранен.";
        } else {
            echo "Ошибка при записи в файл.";
        }
    } else {
        echo "Ошибка при загрузке фото.";
    }
} else {
    echo "Доступ запрещен.";
}
?>