package main

import (
	"time"
	"github.com/dgrijalva/jwt-go"
	"golang.org/x/crypto/bcrypt"
)

var jwtKey = []byte("your_secret_key") // Используйте сильный секретный ключ

// Claims структура для JWT
type Claims struct {
	UserID string `json:"user_id"`
	jwt.StandardClaims
}

// GenerateToken генерирует новый JWT для пользователя
func GenerateToken(userID string) (string, error) {
	expirationTime := time.Now().Add(5 * time.Minute) // Устанавливаем срок действия токена
	claims := &Claims{
		UserID: userID,
		StandardClaims: jwt.StandardClaims{
			ExpiresAt: expirationTime.Unix(),
		},
	}

	token := jwt.NewWithClaims(jwt.SigningMethodHS512, claims)
	tokenString, err := token.SignedString(jwtKey)

	return tokenString, err
}

// GenerateRefreshToken генерирует новый Refresh токен
func GenerateRefreshToken() (string, string, error) {
	refreshToken := make([]byte, 32) // Генерируем байты для токена
	_, err := rand.Read(refreshToken)
	if err != nil {
		return "", "", err
	}

	refreshTokenString := base64.URLEncoding.EncodeToString(refreshToken)
	hashedToken, err := bcrypt.GenerateFromPassword([]byte(refreshTokenString), bcrypt.DefaultCost)
	if err != nil {
		return "", "", err
	}

	return refreshTokenString, string(hashedToken), nil
}

// ValidateRefreshToken проверяет Refresh токен
func ValidateRefreshToken(token, hash string) bool {
	err := bcrypt.CompareHashAndPassword([]byte(hash), []byte(token))
	return err == nil
}

