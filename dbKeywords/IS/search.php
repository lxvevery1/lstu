<?php
    include 'header.php'
?>

<link rel="stylesheet" href="https://cdn.jsdelivr.net/npm/water.css@2/out/light.css">
<button class="home-button" onclick="location.href='http://localhost/dbKeywords/Authentification/index.php'">Home</button>
<h1>Search page</h1>

<div class="words-container">
<?php
    if (isset($_POST['submit-search'])){
        $search = mysqli_real_escape_string($conn, $_POST['search']);
        $sql = "SELECT * FROM keyword WHERE Name LIKE '%$search%' OR Definition LIKE '%$search%' OR cpp_version LIKE '%$search%' OR Type LIKE '%$search%'";
        $result = mysqli_query($conn, $sql);
        $queryResult = mysqli_num_rows($result);

        if ($queryResult > 0) {
            while ($row = mysqli_fetch_assoc($result)) {
                echo "<div class='words-list'>
                <a href='article.php?title=".$row['Name']."&type=".$row['Type']."'>
                <div class='article-box'>
                <h3>".$row['Name']."</h3> 
                <p class='type'>".$row['Type']."</p>
                </div>
                </div>";
            }
        } else {
            echo "There are no results matching your search!";
        }
    }
?>
</div>