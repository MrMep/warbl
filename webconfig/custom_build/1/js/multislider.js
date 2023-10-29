
function fillSliderAuto() {

    slide1 = parseFloat(document.getElementById("lowerBoundRangeHH").value);
    slide2 = parseFloat( document.getElementById("upperBoundRangeHH").value );
    from = document.querySelector('#lowerBoundRangeHH');
    to =  document.querySelector('#upperBoundRangeHH');
    sliderColor = '#999999';
    rangeColor = 'rgb(105, 183, 10)';
    const rangeDistance = to.max-to.min;
    const fromPosition = from.value - to.min;
    const toPosition = to.value - to.min;
    var gradient = `linear-gradient(to right,${sliderColor} 0%,${sliderColor} ${(fromPosition)/(rangeDistance)*100}%,${rangeColor} ${((fromPosition)/(rangeDistance))*100}%, ${rangeColor} ${(toPosition)/(rangeDistance)*100}%, ${sliderColor} ${(toPosition)/(rangeDistance)*100}%, ${sliderColor} 100%)`;
    // console.log(rangeDistance, fromPosition, toPosition, gradient)
    // from.style.background = gradient;
      to.style.background = `linear-gradient(
        to right,
        ${sliderColor} 0%,
        ${sliderColor} ${(fromPosition)/(rangeDistance)*100}%,
        ${rangeColor} ${((fromPosition)/(rangeDistance))*100}%,
        ${rangeColor} ${(toPosition)/(rangeDistance)*100}%, 
        ${sliderColor} ${(toPosition)/(rangeDistance)*100}%, 
        ${sliderColor} 100%)`;

        var displayElement = document.getElementById("double-range-label");
        displayElement.innerHTML = slide1 + " - " + slide2;
        // console.log("fillSliderAuto", slide1, slide2);
}


var slide1 = parseFloat(document.getElementById("lowerBoundRangeHH").value);

var slide2 = parseFloat( document.getElementById("upperBoundRangeHH").value );

function slider_getVals(){

    //Disables user intervention
    document.getElementById("lowerBoundRangeHH").value = slide1;
    document.getElementById("upperBoundRangeHH").value = slide2;
    return;
    // Get slider values
    var slide1_now = parseFloat(document.getElementById("lowerBoundRangeHH").value);
    var slide2_now = parseFloat( document.getElementById("upperBoundRangeHH").value );

    if (slide1_now != slide1) {
        if ( slide1_now > slide2_now-50 ){
            document.getElementById("lowerBoundRangeHH").value = slide1;
             // console.log(slide1, slide2);
            return;
        } else {
            slide1 = slide1_now;
            // sendHalfHoleLowerBound (slide1);
        }
    }

    if (slide2_now != slide2) {
        var slide1_now = parseFloat(document.getElementById("lowerBoundRangeHH").value);
        if ( slide2_now < slide1_now+50 ){
            document.getElementById("upperBoundRangeHH").value = slide2;
              console.log(slide1, slide2);
            return;
        } if ( slide2_now > 499) {
            document.getElementById("upperBoundRangeHH").value = 499;
            return;
        } else {
            slide2 = slide2_now;
            sendHalfHoleUpperBound (slide2);
        }
    }

    fillSliderAuto();
  }

