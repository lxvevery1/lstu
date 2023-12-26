let loader = document.getElementById("loader");
let header = document.querySelector("header");
let main = document.querySelector("main");
let footer = document.querySelector("footer");
let cardBlock = document.getElementById("cardBlock")
let out = document.getElementById('out')

console.log(cardBlock);
console.log(main);

/////////////////// ЭФФЕКТИК ////////////////////////
header.style.opacity = '0';
main.style.opacity = '0';
footer.style.opacity = '0';
cardBlock.style.opacity = '0';


//////////////// ЭФФЕКТИК ////////////////
setTimeout(() => {
  
    header.style.opacity = '1';
    main.style.opacity = '1';
    footer.style.opacity = '1';
    cardBlock.style.opacity = '1';
  
  
    setTimeout(() => {
      loader.style.display = 'none';
    }, 2);
}, 10);

//////////////////// КАРТОЧКИ //////////////////////
class Cloth {
    constructor(id, brand, price, image, description) {
        this.id = id;
        this.brand = brand;
        this.price = price;
        this.image = image;
        this.description = description;
    }

    render() {
        const cardItem = `
          <div class="card_output">
            <img src="${this.image}">
            <p class="price-text">${this.price}<span class="rub"> руб</span></p>
            <p class="brand-text1"><span class="brand1">Бренд</span> ${this.brand}</p>
            <p class="description-text">${this.description}</p>
          </div>
        `;
    
        out.insertAdjacentHTML('afterbegin', cardItem);
      }
      
}

const menuItem = [
    new Cloth(1, 'Каменный остров', 30000, 'img/одежда_1.png', 'Жилет с нашивкой компасом'),
    new Cloth(2, 'АМИ Париж', 18800, 'img/одежда_2.png', 'Полосатая рубашка с коротким рукавом'),
    new Cloth(3, 'Вквадате', 47300, 'img/одежда_3.png', 'Укороченные брюки с вышитым логотипом'),
    new Cloth(4, 'Акне Студия', 19000, 'img/одежда_4.png', 'Полосатый двубортный блейзер')
];


//////////////////// ФИЛЬТР //////////////////////
const checkboxes = document.querySelectorAll('.dropdown-content input[type="checkbox"]');

// Функция для отображения одежды в зависимости от выбранных фильтров
function updateClothDisplay() {
    const selectedBrands = Array.from(checkboxes)
      .filter(checkbox => checkbox.checked)
      .map(checkbox => checkbox.labels[0].textContent);
  
    const filteredClothes = menuItem.filter(item => selectedBrands.includes(item.brand));
  
    // Очищаем контейнер перед обновлением
    out.innerHTML = '';
  
    // Отображаем отфильтрованные элементы
    filteredClothes.forEach(item => item.render());
  }

// Добавляем слушатели событий для чекбоксов
checkboxes.forEach(checkbox => {
  checkbox.addEventListener('change', updateClothDisplay);
  
});

///////////// СОРТИРОВКА ////////////////////
function sortClothes(sortOption) {
    if (sortOption === 'cheap-first') {
        menuItem.sort((a, b) => a.price - b.price);
    } else if (sortOption === 'expensive-first') {
        menuItem.sort((a, b) => b.price - a.price);
    }
    else if (sortOption === 'all') {
        menuItem.sort((a, b) => a.id - b.id);
    }

    updateCardDisplay();
}


///////////// СОРТИРОВКА ////////////////////
function updateCardDisplay() {
    let cardItem = '';
    menuItem.forEach((menu) => {
        cardItem +=
            `
            <div class="card_output" ">
                <img src="${menu.image}">
                <p class="price-text">${menu.price}<span class="rub"> руб</span></p>
                <p class="brand-text1"><span class="brand1">Бренд</span> ${menu.brand}</p>
                <p class="description-text">${menu.description}</p>
            </div>
            `;
    });

    // Clear the existing content and insert updated cards
    out.innerHTML = cardItem;
}


let cardItem = '';

const selectElement = document.getElementById('choose-select');


//////////////////// ЛОГИН ПОПАП ////////////////
document.getElementById('loginButton').addEventListener('click', function() {
    document.getElementById('loginPopup').style.display = 'block';
  });
  
  document.getElementById('closePopup').addEventListener('click', function() {
    document.getElementById('loginPopup').style.display = 'none';
  });
  
  document.addEventListener('keydown', function(event) {
    if (event.key === 'Escape') {
      document.getElementById('loginPopup').style.display = 'none';
    }
  });

document.getElementById('choose-select').addEventListener('change', function () {
    const selectedOption = this.value;
    sortClothes(selectedOption);
  });
  

///////////// КАРТОЧКИ ////////////////////
updateCardDisplay()