import os
import pandas as pd
from sklearn.model_selection import train_test_split
from sklearn.multioutput import MultiOutputRegressor
from sklearn.ensemble import GradientBoostingRegressor
from sklearn.metrics import mean_squared_error
import pickle

def save_model(model, filename):
    # use pickle
    with open(os.path.join('static', 'dataset', filename), 'wb') as f:
        pickle.dump(model, f)

def train_test_uv_pivot(filename):
    df = pd.read_csv(os.path.join('static', 'dataset', filename))
    # 按列分割数据
    df_X = df.iloc[:, :-3]
    df_Y = df.iloc[:, -3:]
    X_train, X_test, Y_train, Y_test = train_test_split(df_X, df_Y, test_size=0.2, random_state=42)
    # 多输出 梯度下降
    multi_gbr = MultiOutputRegressor(
        GradientBoostingRegressor(n_estimators=100, learning_rate=0.1, max_depth=1, random_state=0, loss='squared_error')
    )
    multi_gbr.fit(X_train, Y_train)
    Y_pred = multi_gbr.predict(X_test)
    rmse = mean_squared_error(Y_test, Y_pred)
    print('[RMSE] uv_pivot:', rmse)
    save_model(multi_gbr, 'uv_pivot.pkl')

def train_test_edgeline(filename):
    df = pd.read_csv(os.path.join('static', 'dataset', filename))
    # 按列分割数据
    df_X = df.iloc[:, :-1]
    df_Y = df.iloc[:, -1:]
    X_train, X_test, Y_train, Y_test = train_test_split(df_X, df_Y, test_size=0.2, random_state=42)
    # 单输出 梯度下降
    gbr = GradientBoostingRegressor(n_estimators=100, learning_rate=0.1, max_depth=1, random_state=0, loss='squared_error')
    gbr.fit(X_train, Y_train)
    Y_pred = gbr.predict(X_test)
    rmse = mean_squared_error(Y_test, Y_pred)
    print('[RMSE] edgeline:', rmse)
    save_model(gbr, 'edge_line.pkl')


if __name__ == '__main__':
    train_test_uv_pivot('uv_pivot.csv')
    train_test_edgeline('edge_line.csv')