template<typename T>
bool FUJsonCppWrapper::addNewObject(std::string key, T value, std::string rootObjectName)
{
    if (mLoadedJsonFilePath.size() < 1)
        return false;//No file is loaded
    if (rootObjectName.size() > 1)
        mRootValue[rootObjectName][key] = value;
    else
        mRootValue[key] = value;
    writeStyledJsonFile(mRootValue, mLoadedJsonFilePath);
    return true;
}

template<typename T>
bool FUJsonCppWrapper::addNewArray(std::string key, std::vector<T> &items, std::string rootObjectName)
{
    if (mLoadedJsonFilePath.size() < 1)
        return false;//No file is loaded
    Json::Value arrayValue = rootObjectName.size() > 1 ? mRootValue[rootObjectName][key] : mRootValue[key];
    for (T t : items)
        arrayValue.append(Json::Value(t));
    if (rootObjectName.size() > 1)
        mRootValue[rootObjectName][key] = arrayValue;
    else
        mRootValue[key] = arrayValue;
    writeStyledJsonFile(mRootValue, mLoadedJsonFilePath);
    return true;
}

template<typename T>
bool FUJsonCppWrapper::removeObjectItemFromArray(std::string key, T value, std::string rootObjectName)
{
    if (mLoadedJsonFilePath.size() < 1)
        return false;//No file is loaded
    Json::Value arrayValue = rootObjectName.size() > 1 ? mRootValue[rootObjectName][key] : mRootValue[key];
    //If the value is inside an object in the array, delete that object.
    for (unsigned int i = 0;i < arrayValue.size();i++) {
        if (arrayValue.get(i, Json::Value("null")).isObject()) {
            Json::Value nestedValue = arrayValue.get(i, Json::Value("null"));
            nestedValue.removeMember(value);
            arrayValue[i] = nestedValue;
        }
    }
    //Update the Value
    if (rootObjectName.size() > 1)
        mRootValue[rootObjectName][key] = arrayValue;
    else
        mRootValue[key] = arrayValue;
    //If isNestedArray is false then the value is not an object. This step is executed even if the
    //isNestedArray is true, that is to delete the empty objects i the array
    Json::Value tempValue;
    for (unsigned int i = 0;i < arrayValue.size();i++) {
        if (arrayValue[i] != value && arrayValue[i].empty() == false) {
            tempValue.append(arrayValue[i]);
        }
    }
    //Update the Value
    if (rootObjectName.size() > 1)
        mRootValue[rootObjectName][key] = tempValue;
    else
        mRootValue[key] = tempValue;
    writeStyledJsonFile(mRootValue, mLoadedJsonFilePath);
    return true;
}

template<typename T>
bool FUJsonCppWrapper::removeItemFromArray(std::string key, T value, std::string rootObjectName)
{
    if (mLoadedJsonFilePath.size() < 1)
        return false;//No file is loaded
    Json::Value arrayValue = rootObjectName.size() > 1 ? mRootValue[rootObjectName][key] : mRootValue[key];
    //If isNestedArray is false then the value is not an object. This step is executed even if the
    //isNestedArray is true, that is to delete the empty objects i the array
    Json::Value tempValue;
    for (unsigned int i = 0;i < arrayValue.size();i++) {
        if (arrayValue[i] != value && arrayValue[i].empty() == false) {
            tempValue.append(arrayValue[i]);
        }
    }
    //Update the Value
    if (rootObjectName.size() > 1)
        mRootValue[rootObjectName][key] = tempValue;
    else
        mRootValue[key] = tempValue;
    writeStyledJsonFile(mRootValue, mLoadedJsonFilePath);
    return true;
}

template<typename T>
bool FUJsonCppWrapper::addItemToArray(std::string key, T value, std::string rootObjectName)
{
    if (mLoadedJsonFilePath.size() < 1)
        return false;//No file is loaded
    Json::Value arrayValue = rootObjectName.size() > 1 ? mRootValue[rootObjectName][key] : mRootValue[key];
    arrayValue.append(Json::Value(value));
    if (rootObjectName.size() > 1)
        mRootValue[rootObjectName][key] = arrayValue;
    else
        mRootValue[key] = arrayValue;
    writeStyledJsonFile(mRootValue, mLoadedJsonFilePath);
    return true;
}

template<typename T>
bool FUJsonCppWrapper::addObjectToArray(std::string key, std::vector<std::string> objectKeys, std::vector<T> values, std::string rootObjectName)
{
    if (mLoadedJsonFilePath.size() < 1)
        return false;//No file is loaded
    Json::Value arrayValue = rootObjectName.size() > 1 ? mRootValue[rootObjectName][key] : mRootValue[key];
    Json::Value objectValue;
    for (unsigned int i = 0;i < objectKeys.size();i++) {
        objectValue[objectKeys[i]] = values[i];
    }
    arrayValue.append(objectValue);
    if (rootObjectName.size() > 1)
        mRootValue[rootObjectName][key] = arrayValue;
    else
        mRootValue[key] = arrayValue;
    writeStyledJsonFile(mRootValue, mLoadedJsonFilePath);
    return true;
}

template<typename T>
bool FUJsonCppWrapper::addObjectToArray(std::string key, std::string objectKey, T value, std::string rootObjectName)
{
    if (mLoadedJsonFilePath.size() < 1)
        return false;//No file is loaded
    std::vector<std::string> vectorKey;
    vectorKey.push_back(objectKey);
    std::vector<T> vectorValue;
    vectorValue.push_back(value);
    addObjectToArray(key, vectorKey, vectorValue, rootObjectName);
    return true;
}
