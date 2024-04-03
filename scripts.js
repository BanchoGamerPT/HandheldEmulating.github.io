/*---------------------------------------------------------------------------
---------------------------Template for all pages----------------------------
---------------------------------------------------------------------------*/
const template = document.createElement("template");

template.innerHTML =
    `
    <header class="initialHeader" id="header">
        <h1>Handheld Emulating Digital Console</h1>
    </header>

    <div class="menu-toggle" onclick="toggleMenu()" id="menuButton">☰</div>

    <div class="popup-menu" id="myMenu">
        <h2>Menu</h2>

        <ul>
            <li>
                <a href="index.html" target="_self" id=index>🏠 Home</a>
                <a href="index.html" target="_self" style="float: right; margin-right: var(--emoji-margin)" id=menu_button_1>🏠</a>
            </li>
            <li>
                <a href="product.html" target="_self" id=product>🎮 Product</a>
                <a href="product.html" target="_self" style="float: right; margin-right: var(--emoji-margin)" id=menu_button_2>🎮</a>
            </li>
            <li>
                <a href="downloads.html" target="_self" id=downloads>🔗 Downloads</a>
                <a href="downloads.html" target="_self" style="float: right; margin-right: var(--emoji-margin)" id=menu_button_3>🔗</a>
            </li>
            <li>
                <a href="about.html" target="_self" id=about>🔎 About</a>
                <a href="about.html" target="_self" style="float: right; margin-right: var(--emoji-margin)" id=menu_button_4>🔎</a>
            </li>
            <li>
                <a href="planning.html" target="_self" id=planning>📅 Planning</a>
                <a href="planning.html" target="_self" style="float: right; margin-right: var(--emoji-margin)" id=menu_button_5>📅</a>
            </li>
            <li>
                <a href="changelog.html" target="_self" id=changelog>📝 Blog</a>
                <a href="changelog.html" target="_self" style="float: right; margin-right: var(--emoji-margin)" id=menu_button_6>📝</a>
            </li>
            <li>
                <a href="contacts.html" target="_self" id=contacts>🌐 Contacts</a>
                <a href="contacts.html" target="_self" style="float: right; margin-right: var(--emoji-margin)" id=menu_button_7>🌐</a>
            </li>
        </ul>
        <br>
        <button id="toggleNightMode">Night button emoji</button> <span>Night mode</span>
    </div>
    `
;

/*-------------------------------------------------------------------------------------------------------------------------+
|To switch from the emojis on the menu to images use the following code:                                                   |
|<a href="contacts.html" target="_self">                                                                                   |
|    <img src="https://encrypted-tbn0.gstatic.com/images?q=tbn:ANd9GcQ03J8899E-Vh6SsuEscCHxh6ENeqE4qvTwPA4TFzzJUQ&s"></img>|
|</a>                                                                                                                      |
+-------------------------------------------------------------------------------------------------------------------------*/

document.body.insertBefore(template.content, document.body.firstChild);



/*---------------------------------------------------------------------------
--------------------------Night Mode Functionality---------------------------
---------------------------------------------------------------------------*/
document.addEventListener('DOMContentLoaded', function () {
    const toggleNightModeButton = document.getElementById('toggleNightMode');
    const body = document.body;
    const header = document.getElementById('header');
    const menu = document.getElementById('myMenu');

    // Function to set dark mode based on user preference
    const setDarkMode = (isDarkMode) => {
        body.classList.toggle('dark-mode', isDarkMode);
        header.classList.toggle('dark-mode', isDarkMode);
        menu.classList.toggle('dark-mode', isDarkMode);
    };

    // Check if dark mode preference is stored in local storage
    const isDarkMode = localStorage.getItem('darkMode') === 'true';

    // Apply dark mode based on stored preference
    setDarkMode(isDarkMode);

    if (isDarkMode) {
        toggleNightModeButton.innerText = "☀️";
    } else{
        toggleNightModeButton.innerText = "🌙";
    }

    toggleNightModeButton.addEventListener('click', function () {
        // Toggle dark mode class on body and header
        body.classList.toggle('dark-mode');
        header.classList.toggle('dark-mode');
        menu.classList.toggle('dark-mode');

        // Store the dark mode preference in local storage
        const isDarkModeNow = body.classList.contains('dark-mode');
        localStorage.setItem('darkMode', isDarkModeNow);

        if (isDarkModeNow) {
            toggleNightModeButton.innerText = "☀️";
        } else{
            toggleNightModeButton.innerText = "🌙";
        }
    });
});



/*---------------------------------------------------------------------------
----------------------Current page highlight functionality-------------------
---------------------------------------------------------------------------*/
// Get the current page's filename
var currentPage = window.location.pathname.split('/').pop();

// Remove the ".html" extension
currentPage = currentPage.replace('.html', '');

// Find the corresponding menu link and add the 'active' class
var menuLinks = document.getElementsByTagName('a');
for (var i = 0; i < menuLinks.length; i++) {
    var link = menuLinks[i];
    var linkPage = link.href.split('/').pop().replace('.html', '');

    if (currentPage === linkPage) {
        link.classList.add('active');
    }
}



/*---------------------------------------------------------------------------
------------------------Toggle side-menu functionality-----------------------
---------------------------------------------------------------------------*/
// Variable that stores if the menu is open or closed (it's state)
var isOpen = 0;

// Toggle menu twice to get it in the right position
toggleMenu();
toggleMenu();

function toggleMenu() {
    // Access the menu element
    var menu = document.getElementById('myMenu');

    // Access the root element to access CSS variables
    var root = document.documentElement;

    // Get the value of the --menu-box-width variable as a float
    var width = parseFloat(getComputedStyle(root).getPropertyValue('--menu-box-width'));

    if (width >= 500){
        width -= 85;
    }

    // Altering where the left is
    menu.style.left = menu.style.left === '0px' ? -width + 'px' : '0px';

    // Toggling the emoji buttons on the menu
    for (let i = 1; i < 8; i++){
        // Access the buttons element
        var buttons = document.getElementById("menu_button_" + i);

        // Accessing the display property value
        var displayValue = window.getComputedStyle(buttons).getPropertyValue('display');

        if (displayValue == "block"){
            displayValue = "none";
        } else{
            displayValue = "block";
        }

        buttons.style.display = displayValue
    }

    // Changing the state variable
    if (isOpen){
        isOpen = 0;
    } else{
        isOpen = 1;
    }
}

// Event to close menu if user clicks outside the menu window
window.addEventListener('click', function(e){
    // Check if the click is inside the menu
    if (!document.getElementById("menuButton").contains(e.target) && (!document.getElementById("myMenu").contains(e.target))){
        // If it's open, toggle it to close it
        if (isOpen >= 1){
            toggleMenu();
        }
    } 
})