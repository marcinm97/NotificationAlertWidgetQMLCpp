function checkList() {
    var errorCount = errorCounter();
    if(errorModel.count === 0){
        errorModel.append({"type": 0, "msg" : "No problem detected"})
    }
    else if(errorCount > 0)
    {
        if(errorCount !== errorModel.count){
            removePlaceHolder()
        }
    }
}
function errorCounter(){
    var errorCount = 0;
    for(var i = 0; i < errorModel.count; ++i){
        if(errorModel.get(i).type !== 0){
            errorCount++
        }
    }
    return errorCount

}
function removePlaceHolder(){
    for(var i = 0; i < errorModel.count; ++i){
        if(errorModel.get(i).type === 0){
            errorModel.remove(i)
        }
    }
}
