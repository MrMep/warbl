
function fillSliderAuto() {
    from = document.querySelector('#lowerLimitRangeHH');
    to =  document.querySelector('#upperLimitRangeHH');
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
}


var slide1 = parseFloat(document.getElementById("lowerLimitRangeHH").value);

var slide2 = parseFloat( document.getElementById("upperLimitRangeHH").value );

function slider_getVals(){
    // Get slider values
    var slide1_now = parseFloat(document.getElementById("lowerLimitRangeHH").value);
    var slide2_now = parseFloat( document.getElementById("upperLimitRangeHH").value );

    if (slide1_now != slide1) {
        if ( slide1_now > slide2-50 ){
            document.getElementById("lowerLimitRangeHH").value = slide1;
            // console.log(slide1, slide2);
            return;
        } else {
            slide1 = slide1_now;
            sendHalfHoleLowerLimit (slide1);
        }
    }

    if (slide2_now != slide2) {
        if ( slide2_now < slide1+50 ){
            document.getElementById("upperLimitRangeHH").value = slide2;
            // console.log(slide1, slide2);
        return;
        } else {
            slide2 = slide2_now;
            sendHalfHoleUpperLimit (slide2);
        }
    }

    fillSliderAuto();
  }

