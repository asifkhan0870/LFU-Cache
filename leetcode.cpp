class LFUCache {
public:
     
     int cap;  // This will store the capacity of our cache

     int minFreq;  // this will store the min freq and from we will access the LRU
            //     key  ->> (value,freq)
     unordered_map<int ,pair<int,int>>keyValue;  
            // key  --->> list has atteched to it there may many nodes and list is doubly linkelist
     unordered_map<int,list<int>>freqList;

     unordered_map<int,list<int>::iterator>add;  // this will store the address



    void update(int key){

             // first access the curr freq  

             int curr_freq=keyValue[key].second;

             // now delete this node because we going to update and we have access one times so this node
             // will to the next freq  

             freqList[curr_freq].erase(add[key]);

             // now increment the freq  

             keyValue[key].second++;

              curr_freq=keyValue[key].second;

             // now update the freq 

             freqList[curr_freq].push_back(key);

             // and update the addreess

             add[key]=--freqList[curr_freq].end();


             // caution-->>> it may be we are deleting a node and that freq level only one node and 
             // we delete that so there we node at that so we have to increament our minFreq

             if(freqList[minFreq].empty()){
                 minFreq++;
             }



    }


    // Initialization  
    LFUCache(int capacity) {
          
          cap=capacity;
          minFreq=0;    
    }


    
    int get(int key) {
        
        // there will two case in it 

        // 1. this key is present in our cache

        if(keyValue.find(key)==keyValue.end()){
            return -1;
        }

        // since we are again accessing key so we will again update

        update(key);

        // now return that value 

        return keyValue[key].first;
    }
    
    void put(int key, int value) {


        if(cap==0)return;
        
        // There will three case
        // 1. we have to update means the key is already present 

            if(keyValue.find(key)!=keyValue.end()){
                
                keyValue[key].first=value;

                update(key);
                return;

            }
        // 2. the size of our cache is full then we will go to freqlist and delete the first node and add new(key,value) to cache
           
           if(keyValue.size()==cap){

               int del_freq=freqList[minFreq].front(); 

               keyValue.erase(del_freq);

               add.erase(del_freq);


               freqList[minFreq].pop_front();


           }


        // 3. simply our key is not in our cache as well as we have space

        keyValue[key]={value,1};

        freqList[1].push_back(key);

        add[key]=--freqList[1].end();
       

       minFreq=1;



    }
};

/**
 * Your LFUCache object will be instantiated and called as such:
 * LFUCache* obj = new LFUCache(capacity);
 * int param_1 = obj->get(key);
 * obj->put(key,value);
 */