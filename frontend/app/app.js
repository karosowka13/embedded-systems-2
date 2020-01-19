
$(document).ready(function()
{
    var NavY = $('.nav').offset().top; 
    var stickyNav = function()
    {
        var ScrollY = $(window).scrollTop();
      
        if (ScrollY > NavY) 
        { 
            $('.nav').addClass('sticky');
        }
          
        else
        {
            $('.nav').removeClass('sticky'); 
        }
    };

    stickyNav();

    $(window).scroll(function() 
    {
        stickyNav();
    });
});//sticky menu

//handling JSON file

const isValidElement = element =>{
    return element.name && element.value;
};

 const isValidValue = element => {
    return(!['radio'].includes(element.type) || element.checked);
 };

const formToJSON = elements => [].reduce.call(elements, (data, element) =>{

    if(isValidElement(element)&& isValidValue(element) ) {
    data[element.name] = element.value;
    }
    return data;
}, {});

const handleFormSubmit = (form) =>{
  event.preventDefault();

  const data = formToJSON(form.elements);
  // Demo only: print the form data onscreen as a formatted JSON object.
  const dataContainer = document.getElementsByClassName('results__display')[0];
  // Use `JSON.stringify()` to make the output human-readable JSON.
  dataContainer.textContent = JSON.stringify(data, null, "  ");

};

const task = document.getElementsByClassName('task')[0];
const timer = document.getElementsByClassName('timer')[0];
const queue1 = document.getElementsByClassName('queue1')[0];
//console.log(queue1);
task.addEventListener('submit', function () {handleFormSubmit(task);});
timer.addEventListener('submit', function () {handleFormSubmit(timer);});
queue1.addEventListener('submit', function () {handleFormSubmit(queue1);});




  