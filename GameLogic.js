    function moveTile(model,index,size){
        var j = index % size
        var i = Math.trunc(index/size)
        if(i>0){
            if(model.get(j+(i-1)*size).value === size*size){
                model.move(j+i*size,j+((i-1)*size),1)
                model.move((j+1)+(i-1)*size,j+((i)*size),1)
                return
            }
        }
        if(j>0){
            if(model.get(j-1+i*size).value === size*size){
                model.move(j+(i*size),(j-1)+i*size,1)
                return
            }
        }
        if(j<size-1){
            if(model.get(j+1+i*size).value === size*size){
                model.move(j+i*size,j+1+i*size,1)
                return
            }
        }
        if(i<size-1){
            if(model.get(j+(i+1)*size).value === size*size){
                model.move(j+i*size,j+((i+1)*size),1)
                model.move((j-1)+(i+1)*size,j+(i*size),1)
                return
            }
        }
    }

    function isSolvable(model,size){
        var e
        for(var k = 0; k < size*size; k++){
            if(model.get(k).value === size*size)
                e = k+1
        }
        var n = 0
        for(var i = 0; i < size*size-1; i++){
            if(model.get(i).value !== size*size && model.get(i+1).value!==size*size){
                for(var j = i+1; j < size*size; j++){
                    if(model.get(i).value>model.get(j).value){
                        n += 1
                    }
                }
            }
        }
        return !((n+e)%2)
    }

    function shuffle(model,size){
        for(var i = 0; i < size*size;i++){
            var tmp = model.get(i).value
            var randI = Math.round(Math.random()*(size*size-1))
                model.get(i).value = model.get(randI).value
                model.get(randI).value = tmp
        }
    }

    function isSolved(model,size){
        if(model.get(size*size-1).value !== size*size){
            return false
        }
        for(var j = 0; j < size*size; j++){
            if(j+1 !== model.get(j).value){
                return false
            }
        }
        return true
    }
    function mix(model,size){
            do{
                shuffle(model,size)
                console.log("new model values")
            } while(!isSolvable(model,size))
            console.log("new combination successfully found")
    }
