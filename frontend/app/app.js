
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

const handleFormSubmitTask = (form) =>{
  event.preventDefault()
  const data = formToJSON(form.elements)
  data.index = parseInt(data.index,10)
  if (data.duration){
      data.duration = parseInt(data.duration, 10)
  }
  if (data.priority) {
      data.priority = parseInt(data.priority)
  }
  url = "http://192.168.43.128:5000/task"
    make_request(url, data)
};

const handleFormSubmitTimer = (form) =>{
    event.preventDefault()
    const data = formToJSON(form.elements)
    data.running = (data.running == 'true')
    
    if (data.period){
        data.period = parseInt(data.period, 10)
    }
    if (data.semaphore){
        data.semaphore = parseInt(data.semaphore)
    }
    url = "http://192.168.43.128:5000/timer"
      make_request(url, data)
  };

  const handleFormSubmitQueue = (form) =>{
    event.preventDefault()
    const data = formToJSON(form.elements)
    data.value = parseInt(data.value)
    url = "http://192.168.43.128:5000/queue"
      make_request(url, data)
  };

  const handleFormSubmitSemaphore = (form) =>{
    event.preventDefault()
    const data = formToJSON(form.elements)
    data.index=parseInt(data.index, 10)
    url = "http://192.168.43.128:5000/semaphore"
      make_request(url, data)
  };

function make_request(url, data) {
    const dataContainer = document.getElementsByClassName('results__display')[0];
    dataContainer.textContent = JSON.stringify(data, null, "  ");
    console.log();

    $.ajax({
        type:'POST',
        url:url,
        //dataType: 'json',
        data:JSON.stringify(data),
        //data: data,
        contentType: "application/json",
        sucess: function(data){alert(data);},
        failure: function(errMsg){alert(errMsg);
        }
    });
  
}
const task = document.getElementsByClassName('task')[0];
const timer = document.getElementsByClassName('timer')[0];
const queue = document.getElementsByClassName('queue')[0];
const semaphore = document.getElementsByClassName('semaphore')[0];

task.addEventListener('submit', function () {handleFormSubmitTask(task);});
timer.addEventListener('submit', function () {handleFormSubmitTimer(timer);});
queue.addEventListener('submit', function () {handleFormSubmitQueue(queue);});
semaphore.addEventListener('submit', function () {handleFormSubmitSemaphore(semaphore);});

var term = new Terminal();
term.open(document.getElementById('terminal'));
term.write("\r FreeRTOS-board $")
var socket = new WebSocket("ws://192.168.43.128:5000/ws")
socket.onmessage = function (event) {
    if (event.data){
        console.log(event.data);
        term.write("\n\r FreeRTOS-board $ " + event.data)
    }
  }

  window.onbeforeunload = function () {
    socket.close()
 };