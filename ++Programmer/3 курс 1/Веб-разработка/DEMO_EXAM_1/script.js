class Dessert {
    constructor(type, name, image, description) {
        this.type = type;
        this.name = name;
        this.image = image;
        this.description = description;
    }

    render() {
        const container = document.getElementById('desserts-container');
        const dessertItem = document.createElement('div');
        dessertItem.classList.add('item');
        
        // Добавим класс в зависимости от типа десерта
        dessertItem.classList.add(this.type);

        dessertItem.innerHTML = `
            <img src="${this.image}" alt="${this.name}">
            <h4 class="${this.type}-name">${this.name}</h4>
            <p class="${this.type}-description">${this.description}</p>
            <button class="${this.type}-details-button" onclick="showDetails('${this.name}')">Подробнее</button>
        `;
        container.appendChild(dessertItem);
    }
}
// Sample desserts
const tea1 = new Dessert('tea', 'Лун Цзин, 50г', 'img/tea/lun_czin.png', 
'Один из самых узнаваемых сортов китайского чая.\n Его вкус запоминается на всю жизнь: ореховый, с нотами моря и тыквенных семечек, объёмный и глубокий');
const tea2 = new Dessert('tea', '"Королевский Эрл Грей"\nпакетированный чай', 'img/tea/erl_grey.png', 
'Черный чай с бергамотом - это классика вкуса, уже ставшая традицией. Такой напиток известен уже боле ста лет и является излюбленным сортом чая у англичан.');
const coffee = new Dessert('coffee', 'Шоколад Марагоджип', 'img/coffee/chocolate.png', 
'Густой напиток на основе сорта марагоджип с меньшим содержанием кофеина, чем традиционная арабика. Сочетает в себе оттенки кофе и темного шоколада.');

// Display desserts
const desserts = [tea1, tea2, coffee];
desserts.forEach(dessert => dessert.render());

// Function to show details (replace with your implementation)
function showDetails(name) {
    alert(`Details for ${name}`);
}

// Функция для отображения десертов в соответствии с выбранным фильтром
function renderDesserts(filter) {
    const container = document.getElementById('desserts-container');
    container.innerHTML = ''; // Очищаем контейнер перед отрисовкой

    // Фильтруем десерты в соответствии с выбранным типом
    const filteredDesserts = desserts.filter(dessert => dessert.type === filter || filter === 'all');

    // Отрисовываем отфильтрованные десерты
    filteredDesserts.forEach(dessert => dessert.render());
}

function toggleLoginMenu() {
    const loginMenu = document.getElementById('loginMenu');
    loginMenu.style.display = loginMenu.style.display === 'block' ? 'none' : 'block';
}

function login() {
    // Добавьте вашу логику входа
    alert('Вы вошли!');
}

function forgotPassword() {
    // Добавьте вашу логику восстановления пароля
    alert('Забыли пароль?');
}
// Слушатель события изменения значения фильтра
document.getElementById('filter').addEventListener('change', function () {
    const selectedFilter = this.value;
    renderDesserts(selectedFilter);
});

// Отображаем все десерты при загрузке страницы
renderDesserts('all');

