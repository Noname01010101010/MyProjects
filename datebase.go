package main

import (
	"context"
	"time"
	"go.mongodb.org/mongo-driver/mongo"
	"go.mongodb.org/mongo-driver/mongo/options"
)

var mongoClient *mongo.Client

// InitMongoDB инициализирует подключение к MongoDB
func InitMongoDB() error {
	ctx, cancel := context.WithTimeout(context.Background(), 10*time.Second)
	defer cancel()

	var err error
	mongoClient, err = mongo.Connect(ctx, options.Client().ApplyURI("your_mongodb_uri"))
	return err
}

// SaveRefreshToken сохраняет Refresh токен в базе данных
func SaveRefreshToken(userID, refreshToken, refreshTokenHash string) error {
	collection := mongoClient.Database("your_database").Collection("refresh_tokens")
	ctx, cancel := context.WithTimeout(context.Background(), 5*time.Second)
	defer cancel()

	_, err := collection.InsertOne(ctx, bson.M{
		"user_id":           userID,
		"refresh_token":     refreshTokenHash,
		"original_token":    refreshToken, // Это поле необязательно, зависит от требований безопасности
		"creation_timestamp": time.Now(),
	})

	return err
}

// CheckRefreshToken проверяет наличие и валидность Refresh токена в базе данных
func CheckRefreshToken(refreshToken string) (bool, string) {
	collection := mongoClient.Database("your_database").Collection("refresh_tokens")
	ctx, cancel := context.WithTimeout(context.Background(), 5*time.Second)
	defer cancel()

	var result struct {
		UserID string `bson:"user_id"`
	}
	err := collection.FindOne(ctx, bson.M{"original_token": refreshToken}).Decode(&result)
	if err != nil {
		return false, ""
	}

	return true, result.UserID
}

